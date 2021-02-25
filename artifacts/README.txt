B Image dissolve
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

BW Edge clipping
- Input file	: edge_clipping_user_INPUT1.bmp (Original image)
		  edge_clipping_user_INPUT2.bmp (Edge image)
- Output file	: edge_clipping_user_OUTPUT.bmp
- Settings	: - Brush type: Circle (inside hexagon), Line (outside hexagon)
		  - Brush size: 40
		  - Line width: 5
		  - Line angle: 90

2B Edge detection + user-specified edge clipping
- Input file	: edge_detection_and_clipping_INPUT.bmp
- Output file	: edge_detection_and_clipping_OUTPUT.bmp
- Settings	: - Brush type: Scattered lines
		  - Brush size: 30
		  - Line width: 3
		  - Stroke direction: Gradient
		  - Edge clipping: ON
		  - Edge threshold: 200 (default setting)