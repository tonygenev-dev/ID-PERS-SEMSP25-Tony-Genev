# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/tony/Semester 3/Challenges_and_Workshops/id-pers-semsp-25-tony-genev/ps/pirate_ship_game/build/_deps/googletest-src"
  "/home/tony/Semester 3/Challenges_and_Workshops/id-pers-semsp-25-tony-genev/ps/pirate_ship_game/build/_deps/googletest-build"
  "/home/tony/Semester 3/Challenges_and_Workshops/id-pers-semsp-25-tony-genev/ps/pirate_ship_game/build/_deps/googletest-subbuild/googletest-populate-prefix"
  "/home/tony/Semester 3/Challenges_and_Workshops/id-pers-semsp-25-tony-genev/ps/pirate_ship_game/build/_deps/googletest-subbuild/googletest-populate-prefix/tmp"
  "/home/tony/Semester 3/Challenges_and_Workshops/id-pers-semsp-25-tony-genev/ps/pirate_ship_game/build/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp"
  "/home/tony/Semester 3/Challenges_and_Workshops/id-pers-semsp-25-tony-genev/ps/pirate_ship_game/build/_deps/googletest-subbuild/googletest-populate-prefix/src"
  "/home/tony/Semester 3/Challenges_and_Workshops/id-pers-semsp-25-tony-genev/ps/pirate_ship_game/build/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/tony/Semester 3/Challenges_and_Workshops/id-pers-semsp-25-tony-genev/ps/pirate_ship_game/build/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/tony/Semester 3/Challenges_and_Workshops/id-pers-semsp-25-tony-genev/ps/pirate_ship_game/build/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
