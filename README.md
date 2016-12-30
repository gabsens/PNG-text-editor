# PNG tEXt editor
Command line tool that lets you add tEXt chunks in your .png files.

# Usage :
`pngtext [filepath] [chunk name] [keyword] [payload]`

# Comments : 

Build with g++.

The tool creates a file named "modified.png" in the same folder as the target file.

This tool is intented to be used with the `tEXt` chunk as argument, as it is a legit PNG chunk. The keyword and payload can be anything, letting you hide any text or file inside your innocent .png file.

If the payload or keyword contains special caracters, you need to enclose it with single quotation marks. For example you might type something along this line in your console:

`./pngtext /path/file.png tEXt testKeyword 'F!MxMV2'`

This will add a tEXt chunk with keyword "testKeyword" and text "F!MxMV2"

Will probably fail on Windows.
