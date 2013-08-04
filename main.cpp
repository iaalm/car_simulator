#include "cairo_field.h"
#include "pid.h"
class controler : public control_algorithm{
	private:
		point target;
	public:
		controler(point t):target(t){}
speed operator()(field* f){
	static pid *v,*w;
	speed s;
	double dt = f->get_deltaT();
	point tp;
	car c = f->get_car();
	tp = target - c.postion;
	if(tp.distance() < 0.5){
		puts("done!");
		s.w = s.v = 0;
		return s;
	}
	if(!v){
		w = new pid(correct_degree(tp.degree() - c.w),dt);
		v = new pid(tp.distance(),dt);
	}
	s.w = v->next(correct_degree(tp.degree() - c.w));
	s.v = w->next(tp.distance());
	printf("%lf v:%lf w:%lf\n",correct_degree(tp.degree() - c.w),s.v,s.w);

	return s;
}
};
void* timer(void* data){
	field* f = (field*)data;
	while(1){
		f->next();
		usleep(100000);
	}
}
int main(int argc, char *argv[])
{
	std::vector<line> v;
	line l;
	/*
	l.p[0].x = 10;
	l.p[0].y = 10;
	l.p[1].x = 30;
	l.p[1].y = 30;
	v.push_back(l);
	l.p[0].x = 30;
	l.p[0].y = 30;
	l.p[1].x = 30;
	l.p[1].y = 50;
	v.push_back(l);
	l.p[0].x = 30;
	l.p[0].y = 50;
	l.p[1].x = 10;
	l.p[1].y = 70;
	v.push_back(l);
	l.p[0].x = 10;
	l.p[0].y = 70;
	l.p[1].x = 10;
	l.p[1].y = 10;
	v.push_back(l);
	*/
	l.p[0].x = 350;
	l.p[0].y = 350;
	l.p[1].x = 450;
	l.p[1].y = 450;
	v.push_back(l);
	l.p[0].x = 450;
	l.p[0].y = 350;
	l.p[1].x = 350;
	l.p[1].y = 450;
	v.push_back(l);

	field* f = new cairo_field(*new controler(point(400,400)),v,&argc,&argv,*new car(40,40,0*M_PI,20));
	pthread_t thread;
	pthread_create(&thread,NULL,timer,f);
	cairo_field::start();
	
	return 0;
}
