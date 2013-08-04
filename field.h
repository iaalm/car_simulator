#include <cfloat>
#include <math.h>
#include <vector>
double correct_degree(double degree){
	if(degree >= 0)
		return degree -= (int)(degree / 2 / M_PI + 0.5) * 2 * M_PI;
	else
		return degree -= (int)(degree / 2 / M_PI - 0.5) * 2 * M_PI;

}
struct point{
	double x,y;
	point(){}
	point(double tx,double ty):x(tx),y(ty){}
	point operator-(const point &p)const{
		point t;
		t.x = x - p.x;
		t.y = y - p.y;
		return t;
	}
	double degree(){
		return atan2(y,x);
	}
	double distance(){
		return hypot(y,x);
	}
};
struct line{
	point p[2];
};
/*
class polygon{
	private:
		std::vector<point> vPoint;
};
*/
struct speed{
	double v,w;
};
struct car{
	point postion;
	double w,r;
	car(double tx = 0,double ty = 0,double tw = 0,double tr = 10):postion(tx,ty),w(tw),r(tr){};
};
class field;
class control_algorithm{
	public:
	virtual speed operator()(field*) = 0;
};

class field{
	protected:
		double deltaT;
		car c;
		std::vector<line> vline;
		control_algorithm& algorithm;

		bool is_hit(){return false;}
	public:
		field(
				control_algorithm& alg,
				std::vector<line> vl = *new std::vector<line>(),
				car ca = *new car(),
				double dt = 0.1
				):algorithm(alg),c(ca),deltaT(dt),vline(vl){};
		void next(){
			speed cspeed = algorithm(this);
			c.postion.x += cspeed.v * deltaT * cos(c.w);
			c.postion.y += cspeed.v * deltaT * sin(c.w);
			c.w = correct_degree(c.w + cspeed.w * deltaT);
			//TODO:碰撞检测
			if(is_hit()){}
		}
		const std::vector<line>& get_vline(){return vline;}
		double get_deltaT(){return deltaT;}
		const car& get_car(){return c;}
		double distance(double w){
			double min = DBL_MAX;
			return min;
		}
		//TODO:传感器信息获取函数
};
