import sys
import os
import shlex
import subprocess

read_the_docs_build = os.environ.get('READTHEDOCS', None) == 'True'

if read_the_docs_build:
    subprocess.call('doxygen', shell=True)

extensions = ['breathe']
breathe_projects = { 'Robbie-the-Robot': 'xml' }
breathe_default_project = "Robbie-the-Robot"
templates_path = ['_templates']
source_suffix = '.rst'
master_doc = 'index'
project = u'Robbie-the-Robot'
copyright = u'2015, Robbie-the-Robot'
author = u'Robbie-the-Robot'
version = '1.0'
release = '1.0'
language = None
exclude_patterns = ['_build']
pygments_style = 'sphinx'
todo_include_todos = False
html_static_path = ['_static']
htmlhelp_basename = 'Robbie-the-Robotdoc'
latex_elements = {
}
latex_documents = [
  (master_doc, 'Robbie-the-Robot.tex', u'Robbie-the-Robot Documentation',
   u'Robbie-the-Robot', 'manual'),
]
