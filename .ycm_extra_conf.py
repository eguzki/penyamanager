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
    '-DQT_NETWORK_LIB',
    '-DQT_QML_LIB',
    '-DQT_QUICK_LIB',
    '-DQT_SQL_LIB',
    '-DQT_WIDGETS_LIB',
    '-DQT_XML_LIB',

    '-I', '/usr/include/c++/4.8.2',
    '-I', '/usr/include/x86_64-linux-gnu/c++/4.8',
    '-I', '/usr/include/c++/4.8/backward',
    '-I', '/usr/lib/gcc/x86_64-linux-gnu/4.8/include',
    '-I', '/usr/lib/gcc/x86_64-linux-gnu/4.8/include-fixed',
    '-I', '/usr/include/x86_64-linux-gnu',
    '-I', '/usr/include',

    '-I', '/usr/lib/x86_64-linux-gnu/qt5/mkspecs/linux-g++-64',
    '-I', '/usr/include/qt5',
    '-I', '/usr/include/qt5/QtConcurrent',
    '-I', '/usr/include/qt5/QtCore',
    '-I', '/usr/include/qt5/QtDBus',
    '-I', '/usr/include/qt5/QtGui',
    '-I', '/usr/include/qt5/QtHelp',
    '-I', '/usr/include/qt5/QtMultimedia',
    '-I', '/usr/include/qt5/QtMultimediaWidgets',
    '-I', '/usr/include/qt5/QtNetwork',
    '-I', '/usr/include/qt5/QtOpenGL',
    '-I', '/usr/include/qt5/QtPlatformSupport',
    '-I', '/usr/include/qt5/QtPositioning',
    '-I', '/usr/include/qt5/QtScript',
    '-I', '/usr/include/qt5/QtScriptTools',
    '-I', '/usr/include/qt5/QtSql',
    '-I', '/usr/include/qt5/QtSvg',
    '-I', '/usr/include/qt5/QtTest',
    '-I', '/usr/include/qt5/QtUiTools',
    '-I', '/usr/include/qt5/QtV8',
    '-I', '/usr/include/qt5/QtWebKit',
    '-I', '/usr/include/qt5/QtWebKitWidgets',
    '-I', '/usr/include/qt5/QtWidgets',
    '-I', '/usr/include/qt5/QtXml',
    '-I', '/usr/include/qt5/QtXmlPatterns',

    '-I', 'penyamanager',
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

