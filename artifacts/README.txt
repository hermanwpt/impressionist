IMPORTANT: Please restart the program after testing each requirement to avoid some memory issues (especially when loading large images).
Professor Tang said in class that performance is not a concern for the Impressionist project.

B Dissolve
- Input file	: dissolve_INPUT1.bmp (Original image)
		  dissolve_INPUT2.bmp (Another image)
- Output file	: dissolve_OUTPUT.bmp
- Settings	: For another image:
		  - Brush type: Lines
		  - Brush size: 12
		  - Line width: 2
		  - Spacing: 3
		  - Size rand: OFF
		  - Alpha: 0.20
		  - Stroke direction: Slider
		  - Line angle: 0
		  - Edge clipping: OFF

B RGB Scale
BW Edge clipping
- Input file	: edge_clipping_user_INPUT1.bmp (Original image)
		  edge_clipping_user_INPUT2.bmp (Edge image)
- Output file	: edge_clipping_user_OUTPUT.bmp

2B Edge detection + user-specified edge clipping
- Input file	: edge_detection_and_clipping_INPUT.bmp
- Output file	: edge_detection_and_clipping_OUTPUT.bmp
- Settings	: - Brush type: Scattered lines
		  - Brush size: 30
		  - Line width: 3
		  - Stroke direction: Gradient
		  - Edge clipping: ON
		  - Edge threshold: 200 (default setting)

BW Gradient from user-specified image
BW Automatic paint whole image
- Input file	: ferry.bmp (Original image)
		  ferry-gradient-circular (Another image)
- Output file	: gradient_user_OUTPUT
- Settings	: - Brush type: Lines
		  - Brush size: 7
		  - Brush width: 2
		  - Stroke direction: Gradient
		  - Edge clipping: ON
		  - Another image: ON
		  - Spacing: 1
		  - Size rand.: OFF

2B user-specified kernel
- Input: Input kernel in row major order with each element separated by a " ". Input the size of the kernel.
- Example of inputting kernel {	{1, 2, 3},
								{4, 5, 6},
								{7, 8, 9} }
  Input					Input				Input					Input
  1 2 3 4 5 6 7 8 9		3					Check Normalized Box	Click Apply Button
  in the Kernel Box.	in the Size Box.	
