# PNG tEXt editor
Command line tool that lets you add tEXt chunks in your .png files.

# Usage :
`pngtext [filepath] [chunk name] [keyword] [payload]`

# Comments : 

The tool creates a file named "modified.png" in the same folder as the target file.

This tool is intented to be used with the `tEXt` chunk as argument, as it is a legit PNG chunk. The keyword and payload can be anything, letting you hide any text or file inside your innocent .png file.

Will probably fail on Windows.
