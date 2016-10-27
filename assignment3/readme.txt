John Zeiders
zeiders@usc.edu
Prelab
1.266 is the smallest, as 5 points of will be required on each side.
The upper corner will be (N-1)/2,(N-1)/2 conveniently N/2 in INT math. The Bottom
right will be at 255 + (N-1)/2, 255 + (N-1)/2
2.
RAW
0.7788|0.8824|0.7788|
0.8824|1|0.8824|
0.7788|0.8824|0.7788|
Normalized
0.1018|0.1154|0.1018|
0.1154|0.1308|0.1154|
0.1018|0.1154|0.1018|
If the raw is used the photo ends up majority whited out, as each pixel is
roughly the sum of its neighbors rather than a rough average.

Experimentation:
1. As sigma increases the "blurriness" of the image increases. For sigma <0.5
the image barely changes.
As N increases the image appears more matte and the "blurriness increases".
2. The Sobel filter highlights lines
3. They do not provide inverses for two reasons, the first is the alpha, which
results in the Gaussian not being fully undone. Additionally, if there was any
clamping done on the Gaussian it causes distortions when inverted.

Read ME:
It is N^2, as each pixel will be calculated N*N times.
