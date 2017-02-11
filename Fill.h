#ifndef _FILL_H_
#define _FILL_H_

// data structure to store a coordinate

typedef struct { int x,y;} XYPixel ;


int PushPixel(XYPixel p1);
int PopPixel(XYPixel *theXYPixel);
int IsStackEmpty(void);
void Fill(int _x, int _y, int _FillColour, int _BoundaryColour);

#endif /* _FILL_H_ */
