#ifndef EDGEL_H
#define EDGEL_H

#include <vector>

class Edgel
{
private:
	unsigned int x, y, theta;
public:
	Edgel(void) { x = 0; y = 0; theta = 0;}
	Edgel(unsigned x_, unsigned y_, unsigned theta_) { x = x_; y = y_; theta = theta_;}
	int idx(void) { return (x * 10000 + y * 10 + theta); } //map (x,y,theta) to a unique integer
};

typedef std::vector<int> Content_Vec;

#endif