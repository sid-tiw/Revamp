objDeps = main.o operations.o arguments.o
bin_PROGRAMS = revamp
revamp_SOURCES = main.cpp operations.cpp arguments.cpp operations.h arguments.h colors.h
dist_doc_DATA = README
revamp_CXXFLAGS = -std=c++17 -lstdc++fs

#clean-local :
#	rm revamp $(objDeps) aclocal.m4 config.h.in configure install-sh compile missing depcomp -R autom4te.cache config.status stamp-h1 config.log Makefile.in Makefile -R revamp-1.0 revamp-1.0.tar.gz

# $(bin_PROGRAMS) : $(objDeps)
# 		$(CXX) -o revamp $(objDeps)
# main.o : main.cpp arguments.o
# 		$(CXX) -c main.cpp -std=c++17
# operations.o : operations.cpp operations.h
# 			$(CXX) -c operations.cpp -std=c++17
# arguments.o : arguments.cpp arguments.h operations.o operations.h
# 			$(CXX) -c arguments.cpp -std=c++17
