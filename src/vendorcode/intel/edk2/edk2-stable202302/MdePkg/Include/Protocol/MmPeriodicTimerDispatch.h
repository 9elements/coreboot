/** @file
  MM Periodic Timer Dispatch Protocol as defined in PI 1.5 Specification
  Volume 4 Management Mode Core Interface.

  This protocol provides the parent dispatch service for the periodical timer MMI source generator.

  Copyright (c) 2017, Intel Corporation. All rights reserved.<BR>
  SPDX-License-Identifier: BSD-2-Clause-Patent

  @par Revision Reference:
  This protocol is from PI Version 1.5.

**/

#ifndef _MM_PERIODIC_TIMER_DISPATCH_H_
#define _MM_PERIODIC_TIMER_DISPATCH_H_

#include <Pi/PiMmCis.h>

#define EFI_MM_PERIODIC_TIMER_DISPATCH_PROTOCOL_GUID \
  { \
    0x4cec368e, 0x8e8e, 0x4d71, {0x8b, 0xe1, 0x95, 0x8c, 0x45, 0xfc, 0x8a, 0x53 } \
  }

///
/// Example: A chipset supports periodic MMIs on every 64ms or 2 seconds.
///   A child wishes schedule a period MMI to fire on a period of 3 seconds, there
///   are several ways to approach the problem:
///   1. The child may accept a 4 second periodic rate, in which case it registers with
///        Period = 40000
///        MmiTickInterval = 20000
///      The resulting MMI will occur every 2 seconds with the child called back on
///      every 2nd MMI.
///      NOTE: the same result would occur if the child set MmiTickInterval = 0.
///   2. The child may choose the finer granularity MMI (64ms):
///        Period = 30000
///        MmiTickInterval = 640
///      The resulting MMI will occur every 64ms with the child called back on
///      every 47th MMI.
///      NOTE: the child driver should be aware that this will result in more
///        MMIs occuring during system runtime which can negatively impact system
///        performance.
///
typedef struct {
  ///
  /// The minimum period of time in 100 nanosecond units that the child gets called. The
  /// child will be called back after a time greater than the time Period.
  ///
  UINT64    Period;
  ///
  /// The period of time interval between MMIs. Children of this interface should use this
  /// field when registering for periodic timer intervals when a finer granularity periodic
  /// MMI is desired.
  ///
  UINT64    MmiTickInterval;
} EFI_MM_PERIODIC_TIMER_REGISTER_CONTEXT;

///
/// The DispatchFunction will be called with Context set to the same value as was passed into
/// Register() in RegisterContext and with CommBuffer pointing to an instance of
/// EFI_MM_PERIODIC_TIMER_CONTEXT and CommBufferSize pointing to its size.
///
typedef struct {
  ///
  /// ElapsedTime is the actual time in 100 nanosecond units elapsed since last called, a
  /// value of 0 indicates an unknown amount of time.
  ///
  UINT64    ElapsedTime;
} EFI_MM_PERIODIC_TIMER_CONTEXT;

typedef struct _EFI_MM_PERIODIC_TIMER_DISPATCH_PROTOCOL EFI_MM_PERIODIC_TIMER_DISPATCH_PROTOCOL;

/**
  Register a child MMI source dispatch function for MM periodic timer.

  This service registers a function (DispatchFunction) which will be called when at least the
  amount of time specified by RegisterContext has elapsed. On return, DispatchHandle
  contains a unique handle which may be used later to unregister the function using UnRegister().
  The DispatchFunction will be called with Context set to the same value as was passed into
  this function in RegisterContext and with CommBuffer pointing to an instance of
  EFI_MM_PERIODIC_TIMER_CONTEXT and CommBufferSize pointing to its size.

  @param[in]  This               Pointer to the EFI_MM_PERIODIC_TIMER_DISPATCH_PROTOCOL instance.
  @param[in]  DispatchFunction   Function to register for handler when at least the specified amount
                                 of time has elapsed.
  @param[in]  RegisterContext    Pointer to the dispatch function's context.
                                 The caller fills this context in before calling
                                 the register function to indicate to the register
                                 function the period at which the dispatch function
                                 should be invoked.
  @param[out] DispatchHandle     Handle generated by the dispatcher to track the function instance.

  @retval EFI_SUCCESS            The dispatch function has been successfully
                                 registered and the MMI source has been enabled.
  @retval EFI_DEVICE_ERROR       The driver was unable to enable the MMI source.
  @retval EFI_INVALID_PARAMETER  RegisterContext is invalid. The period input value
                                 is not within valid range.
  @retval EFI_OUT_OF_RESOURCES   There is not enough memory (system or MM) to manage this child.
**/
typedef
EFI_STATUS
(EFIAPI *EFI_MM_PERIODIC_TIMER_REGISTER)(
  IN CONST EFI_MM_PERIODIC_TIMER_DISPATCH_PROTOCOL    *This,
  IN       EFI_MM_HANDLER_ENTRY_POINT                 DispatchFunction,
  IN CONST EFI_MM_PERIODIC_TIMER_REGISTER_CONTEXT     *RegisterContext,
  OUT      EFI_HANDLE                                 *DispatchHandle
  );

/**
  Unregisters a periodic timer service.

  This service removes the handler associated with DispatchHandle so that it will no longer be
  called when the time has elapsed.

  @param[in] This                Pointer to the EFI_MM_PERIODIC_TIMER_DISPATCH_PROTOCOL instance.
  @param[in] DispatchHandle      Handle of the service to remove.

  @retval EFI_SUCCESS            The service has been successfully removed.
  @retval EFI_INVALID_PARAMETER  The DispatchHandle was not valid.
**/
typedef
EFI_STATUS
(EFIAPI *EFI_MM_PERIODIC_TIMER_UNREGISTER)(
  IN CONST EFI_MM_PERIODIC_TIMER_DISPATCH_PROTOCOL  *This,
  IN       EFI_HANDLE                               DispatchHandle
  );

/**
  Returns the next MMI tick period supported by the chipset.

  The order returned is from longest to shortest interval period.

  @param[in]     This             Pointer to the EFI_MM_PERIODIC_TIMER_DISPATCH_PROTOCOL instance.
  @param[in,out] MmiTickInterval  Pointer to pointer of next shorter MMI interval
                                  period supported by the child. This parameter works as a get-first,
                                  get-next field.The first time this function is called, *MmiTickInterval
                                  should be set to NULL to get the longest MMI interval.The returned
                                  *MmiTickInterval should be passed in on subsequent calls to get the
                                  next shorter interval period until *MmiTickInterval = NULL.

  @retval EFI_SUCCESS             The service returned successfully.
**/
typedef
EFI_STATUS
(EFIAPI *EFI_MM_PERIODIC_TIMER_INTERVAL)(
  IN CONST EFI_MM_PERIODIC_TIMER_DISPATCH_PROTOCOL  *This,
  IN OUT UINT64                                     **MmiTickInterval
  );

///
/// Interface structure for the MM Periodic Timer Dispatch Protocol
///
/// This protocol provides the parent dispatch service for the periodical timer MMI source generator.
///
struct _EFI_MM_PERIODIC_TIMER_DISPATCH_PROTOCOL {
  EFI_MM_PERIODIC_TIMER_REGISTER      Register;
  EFI_MM_PERIODIC_TIMER_UNREGISTER    UnRegister;
  EFI_MM_PERIODIC_TIMER_INTERVAL      GetNextShorterInterval;
};

extern EFI_GUID  gEfiMmPeriodicTimerDispatchProtocolGuid;

#endif
