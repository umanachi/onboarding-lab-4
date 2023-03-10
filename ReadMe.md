# Week 4 Lab: Verification Toolchain

## Questions

###### What is a registry?
+ A registry holds the information about a project's packages and points to a repository that holds the packages.

###### What is a package?
+ A package is a collection of source code files for a project.

###### What's the difference between an interface library and a "normal" library or executable? Can you think of any uses for this besides System Verilog files?
+ An interface library can have code that isn't compiled right away, which is good for SV files since they can't be directly compiled. Normal libraries and executables need to be compiled immediately. Interface libraries could be useful as a library of just header files that won't be compiled directly.

###### What is a top module?
+ Top modules are modules that we want to use externally for simulations. In these labs, the top modules are the Exercises, while the Mysteries are not top modules since they are used within Exercise3 and are not directly used for simulation.