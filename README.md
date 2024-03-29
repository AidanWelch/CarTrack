# CarTrack
An open-source tool to track and identify cars on publicly accessible traffic cameras.

## Build

### Prerequisites
- CMake
- Ninja
- clang-tidy-18 and clang-format-18

Tip:
See [llvm repositories](https://apt.llvm.org/)


### Building

1. Run relevant build script with `./build.sh Debug` or `./build.sh Release`
2. Run the command `ninja` to build after changes
3. ~~Profit~~ Run the executable in `bin` or `test` in `build` 

### Tasks
- Decide on appropriate data structures for quick nearest camera queries, little to no random insertion or deletion.

Disclaimer:
This tool is provided under absolutely no guarantee of accuracy.  Like any AI system
it is fallible and should not be considered any form of proof of guilt, especially
in a court of law.  By using this tool you agree to not use as any form of evidence
of guilt, or liability- but it may be used in defense as it can cast reasonable doubt.