# This file is NOT licensed under the GPLv3, which is the license for the rest
# of YouCompleteMe.
#
# Here's the license text for this file:
#
# This is free and unencumbered software released into the public domain.
#
# Anyone is free to copy, modify, publish, use, compile, sell, or
# distribute this software, either in source code form or as a compiled
# binary, for any purpose, commercial or non-commercial, and by any
# means.
#
# In jurisdictions that recognize copyright laws, the author or authors
# of this software dedicate any and all copyright interest in the
# software to the public domain. We make this dedication for the benefit
# of the public at large and to the detriment of our heirs and
# successors. We intend this dedication to be an overt act of
# relinquishment in perpetuity of all present and future rights to this
# software under copyright law.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
# IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
# OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
# ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
# OTHER DEALINGS IN THE SOFTWARE.
#
# For more information, please refer to <http://unlicense.org/>

import os
import ycm_core
from clang_helpers import PrepareClangFlags

# These are the compilation flags that will be used in case there's no
# compilation database set (by default, one is not set).
# CHANGE THIS LIST OF FLAGS. YES, THIS IS THE DROID YOU HAVE BEEN LOOKING FOR.
flags = [
    '-DDEBUG',
    '-Wall',
    '-Wextra',
    '-Werror',
    '-Wno-long-long',
    '-Wno-variadic-macros',
    '-fexceptions',
    '-DUSE_CLANG_COMPLETER',
    # THIS IS IMPORTANT! Without a "-std=<something>" flag, clang won't know
    # which
    # language to use when compiling headers. So it will guess. Badly. So C++
    # headers will be compiled as C headers. You don't want that so ALWAYS
    # specify
    # a "-std=<something>".
    # For a C project, you would set this to something like 'c99' instead of
    # 'c++11'.
    '-std=c++11',
    # ...and the same thing goes for the magic -x option which specifies the
    # language that the files to be compiled are written in. This is mostly
    # relevant for c++ headers.
    # For a C project, you would set this to 'c' instead of 'c++'.
    '-x',
    'c++',

    '-DQT_CORE_LIB',
    '-DQT_GUI_LIB',
    '-DQT_SQL_LIB',
    '-DQT_WIDGETS_LIB',
    '-DQT_NETWORK_LIB',

    '-I', '/usr/include/c++/5.2.1',
    '-I', '/usr/include/x86_64-linux-gnu/c++/5.2.1',
    '-I', '/usr/include/c++/5.2.1/backward',
    '-I', '/usr/lib/gcc/x86_64-linux-gnu/5.2.1/include',
    '-I', '/usr/lib/gcc/x86_64-linux-gnu/5.2.1/include-fixed',
    '-I', '/usr/include/x86_64-linux-gnu',
    '-I', '/usr/include',

    '-I', '/opt/Qt/5.5/gcc_64/include',
    '-I', '/opt/Qt/5.5/gcc_64/include/QtConcurrent',
    '-I', '/opt/Qt/5.5/gcc_64/include/QtCore',
    '-I', '/opt/Qt/5.5/gcc_64/include/QtPrintSupport',
    '-I', '/opt/Qt/5.5/gcc_64/include/QtDBus',
    '-I', '/opt/Qt/5.5/gcc_64/include/QtGui',
    '-I', '/opt/Qt/5.5/gcc_64/include/QtHelp',
    '-I', '/opt/Qt/5.5/gcc_64/include/QtMultimedia',
    '-I', '/opt/Qt/5.5/gcc_64/include/QtMultimediaWidgets',
    '-I', '/opt/Qt/5.5/gcc_64/include/QtNetwork',
    '-I', '/opt/Qt/5.5/gcc_64/include/QtOpenGL',
    '-I', '/opt/Qt/5.5/gcc_64/include/QtPlatformSupport',
    '-I', '/opt/Qt/5.5/gcc_64/include/QtPositioning',
    '-I', '/opt/Qt/5.5/gcc_64/include/QtScript',
    '-I', '/opt/Qt/5.5/gcc_64/include/QtScriptTools',
    '-I', '/opt/Qt/5.5/gcc_64/include/QtSql',
    '-I', '/opt/Qt/5.5/gcc_64/include/QtSvg',
    '-I', '/opt/Qt/5.5/gcc_64/include/QtTest',
    '-I', '/opt/Qt/5.5/gcc_64/include/QtUiTools',
    '-I', '/opt/Qt/5.5/gcc_64/include/QtV8',
    '-I', '/opt/Qt/5.5/gcc_64/include/QtWebKit',
    '-I', '/opt/Qt/5.5/gcc_64/include/QtWebKitWidgets',
    '-I', '/opt/Qt/5.5/gcc_64/include/QtWidgets',
    '-I', '/opt/Qt/5.5/gcc_64/include/QtXml',
    '-I', '/opt/Qt/5.5/gcc_64/include/QtXmlPatterns',

    '-I', 'penyamanager',
    '-I', 'penyamanager/libs/simplecrypt',
    '-I', 'penyamanager/libs/QsLog2',
    '-I', 'penyamanager/libs/mustache',
    '-I', 'dist'
]

def DirectoryOfThisScript():
  return os.path.dirname( os.path.abspath( __file__ ) )

# Set this to the absolute path to the folder (NOT the file!) containing the
# compile_commands.json file to use that instead of 'flags'. See here for
# more details: http://clang.llvm.org/docs/JSONCompilationDatabase.html
#
# Most projects will NOT need to set this to anything; you can just change the
# 'flags' list of compilation flags. Notice that YCM itself uses that approach.
compilation_database_folder = None

if compilation_database_folder:
  database = ycm_core.CompilationDatabase( compilation_database_folder )
else:
  database = None

def MakeRelativePathsInFlagsAbsolute( flags, working_directory ):
  if not working_directory:
    return flags
  new_flags = []
  make_next_absolute = False
  path_flags = [ '-isystem', '-I', '-iquote', '--sysroot=' ]
  for flag in flags:
    new_flag = flag

    if make_next_absolute:
      make_next_absolute = False
      if not flag.startswith( '/' ):
        new_flag = os.path.join( working_directory, flag )

    for path_flag in path_flags:
      if flag == path_flag:
        make_next_absolute = True
        break

      if flag.startswith( path_flag ):
        path = flag[ len( path_flag ): ]
        new_flag = path_flag + os.path.join( working_directory, path )
        break

    if new_flag:
      new_flags.append( new_flag )
  return new_flags


def FlagsForFile( filename ):
  if database:
    # Bear in mind that compilation_info.compiler_flags_ does NOT return a
    # python list, but a "list-like" StringVec object
    compilation_info = database.GetCompilationInfoForFile( filename )
    final_flags = PrepareClangFlags(
        MakeRelativePathsInFlagsAbsolute(
            compilation_info.compiler_flags_,
            compilation_info.compiler_working_dir_ ),
        filename )

    # NOTE: This is just for YouCompleteMe; it's highly likely that your project
    # does NOT need to remove the stdlib flag. DO NOT USE THIS IN YOUR
    # ycm_extra_conf IF YOU'RE NOT 100% YOU NEED IT.
    try:
      final_flags.remove( '-stdlib=libc++' )
    except ValueError:
      pass
  else:
    relative_to = DirectoryOfThisScript()
    final_flags = MakeRelativePathsInFlagsAbsolute( flags, relative_to )

  return {
    'flags': final_flags,
    'do_cache': True
  }

