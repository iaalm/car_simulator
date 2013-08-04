class pid{
	private:
		double deltaT,fe,old_e,k_p,k_i,k_d;
	public:
		pid(double tg,double dt = 0.1,double kp = 0.1,double ki = 0.0000,double kd = 0.0000)
			:deltaT(dt),fe(0),old_e(tg),k_i(ki),k_p(kp),k_d(kd){}
		double next(double e,double dt){
			double t;
			fe += e * dt;
			t = k_p * e + k_i * fe + k_d * (e - old_e) / dt;
			old_e = e;
			return t;
		}
		double next(double now){
			next(now,deltaT);
		}
};
