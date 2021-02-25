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
