# -*- coding: utf-8 -*-
import subprocess
from recommonmark.parser import CommonMarkParser
import sphinx

# Get Sphinx version
major = 0
minor = 0
patchlevel = 0
version = sphinx.__version__.split(".")
if len(version) > 1:
	major = int(version[0])
	minor = int(version[1])
	if len(version) > 2:
		patchlevel = int(version[2])

# Add any paths that contain templates here, relative to this directory.
templates_path = ['_templates']

# The suffix(es) of source filenames.
source_suffix = ['.md']

# The master toctree document.
master_doc = 'index'

# General information about the project.
project = u'coreboot'
copyright = u'CC-by 4.0 the coreboot project'
author = u'the coreboot project'

# The version info for the project you're documenting, acts as replacement for
# |version| and |release|, also used in various other places throughout the
# built documents.
#
# The full version, including alpha/beta/rc tags.
release = subprocess.check_output(('git', 'describe')).decode("utf-8")
# The short X.Y version.
version = release.split("-")[0]

extensions = []
# Load recommonmark, supported since 1.8+
if major >= 2 or (major == 1 and minor >= 8):
    extensions += ['recommonmark']

# Try to load DITAA
try:
    import sphinxcontrib.ditaa
except ImportError:
    print("Error: Please install sphinxcontrib.ditaa for ASCII art conversion\n")
else:
    extensions += ['sphinxcontrib.ditaa']

# The language for content autogenerated by Sphinx. Refer to documentation
# for a list of supported languages.
#
# This is also used if you do content translation via gettext catalogs.
# Usually you set "language" from the command line for these cases.
language = None

# List of patterns, relative to source directory, that match files and
# directories to ignore when looking for source files.
# This patterns also effect to html_static_path and html_extra_path
exclude_patterns = ['_build', 'Thumbs.db', '.DS_Store']

# The name of the Pygments (syntax highlighting) style to use.
pygments_style = 'sphinx'

# A list of ignored prefixes for module index sorting.
# modindex_common_prefix = []

# If true, keep warnings as "system message" paragraphs in the built documents.
# keep_warnings = False

# If true, `todo` and `todoList` produce output, else they produce nothing.
todo_include_todos = False


# -- Options for HTML output ----------------------------------------------

# The theme to use for HTML and HTML Help pages.  See the documentation for
# a list of builtin themes.
#
html_theme = 'sphinx_rtd_theme'

# Add any paths that contain custom static files (such as style sheets) here,
# relative to this directory. They are copied after the builtin static files,
# so a file named "default.css" will overwrite the builtin "default.css".
html_static_path = ['_static']

html_context = {
      'css_files': [
        '_static/theme_overrides.css',  # override wide tables in RTD theme
      ],
}

# Output file base name for HTML help builder.
htmlhelp_basename = 'corebootdoc'

# -- Options for LaTeX output ---------------------------------------------

latex_elements = {
     # The paper size ('letterpaper' or 'a4paper').
     #
     # 'papersize': 'letterpaper',

     # The font size ('10pt', '11pt' or '12pt').
     #
     # 'pointsize': '10pt',

     # Additional stuff for the LaTeX preamble.
     #
     # 'preamble': '',

     # Latex figure (float) alignment
     #
     # 'figure_align': 'htbp',
}

# Grouping the document tree into LaTeX files. List of tuples
# (source start file, target name, title,
#  author, documentclass [howto, manual, or own class]).
latex_documents = [
    (master_doc, 'coreboot.tex', u'coreboot Documentation',
     u'the coreboot project', 'manual'),
]

# The name of an image file (relative to this directory) to place at the top of
# the title page.
#
# latex_logo = None

# For "manual" documents, if this is true, then toplevel headings are parts,
# not chapters.
#
# latex_use_parts = False

# If true, show page references after internal links.
#
# latex_show_pagerefs = False

# If true, show URL addresses after external links.
#
# latex_show_urls = False

# Documents to append as an appendix to all manuals.
#
# latex_appendices = []

# If false, will not define \strong, \code,	itleref, \crossref ... but only
# \sphinxstrong, ..., \sphinxtitleref, ... To help avoid clash with user added
# packages.
#
# latex_keep_old_macro_names = True

# If false, no module index is generated.
#
# latex_domain_indices = True


# -- Options for manual page output ---------------------------------------

# One entry per manual page. List of tuples
# (source start file, name, description, authors, manual section).
man_pages = [
    (master_doc, 'coreboot', u'coreboot Documentation',
     [author], 1)
]

# If true, show URL addresses after external links.
#
# man_show_urls = False


# -- Options for Texinfo output -------------------------------------------

# Grouping the document tree into Texinfo files. List of tuples
# (source start file, target name, title, author,
#  dir menu entry, description, category)
texinfo_documents = [
    (master_doc, 'coreboot', u'coreboot Documentation',
     author, 'coreboot', 'One line description of project.',
     'Miscellaneous'),
]

enable_auto_toc_tree = True

class MyCommonMarkParser(CommonMarkParser):
    # remove this hack once upstream RecommonMark supports inline code
    def visit_code(self, mdnode):
        from docutils import nodes
        n = nodes.literal(mdnode.literal, mdnode.literal)
        self.current_node.append(n)

# Documents to append as an appendix to all manuals.
#
# texinfo_appendices = []

# If false, no module index is generated.
#
# texinfo_domain_indices = True

# How to display URL addresses: 'footnote', 'no', or 'inline'.
#
# texinfo_show_urls = 'footnote'

# If true, do not generate a @detailmenu in the "Top" node's menu.
#
# texinfo_no_detailmenu = False


def setup(app):
    from recommonmark.transform import AutoStructify
    # Load recommonmark on old Sphinx
    if major == 1 and minor < 8:
        app.add_source_parser('.md', MyCommonMarkParser)

    app.add_config_value('recommonmark_config', {
        'enable_auto_toc_tree': True,
        'enable_auto_doc_ref': False, # broken in Sphinx 1.6+
        'enable_eval_rst': True,
        'url_resolver': lambda url: '/' + url
    }, True)
    app.add_transform(AutoStructify)
