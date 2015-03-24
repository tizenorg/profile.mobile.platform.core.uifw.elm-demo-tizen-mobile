#This script is for compiling on PC
#      how to run on PC
#     ===================
#    #cd workdir/bin
#    #./elm-demo-tizen-tv <edje file path>
#    e.g. ./elm-demo-tizen-tv /home/ami/work/efl-theme-tizen-tv.edj
#   This script will be removed later after completion of work.
#
#
#Use gbs for foxp build
mkdir -p ${PWD}/workdir
export PROJECT_HOME=${PWD}/workdir
libtoolize
autoreconf -ivf
./configure --prefix ${PROJECT_HOME}  LDFLAGS=-L${PROJECT_HOME}/lib
