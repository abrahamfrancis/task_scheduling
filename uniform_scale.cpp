#include "schedule.hpp"

schedule uniform_scale(const schedule &sched) {
	double f_lp = 0.65, f_hp = 0.81;
	schedule scaled;
	unsigned int i = 0, j = 0;
	while (i < sched.LP.size() && j < sched.HP.size()) {
		double lp_end = sched.LP[i].start + sched.LP[i].t.lp_size(),
		       hp_end = sched.HP[j].start + sched.HP[j].t.size();
		if (std::abs(sched.HP[j].start - lp_end) <= delta) {
			scaled.add_LP_slot(sched.LP[i].t, f_lp);
			scaled.wait();
			++i;
		} else if (std::abs(sched.LP[i].start - hp_end) <= delta) {
			scaled.add_HP_slot(sched.HP[j].t, f_hp);
			scaled.wait();
			++j;
		} else {
			if (lp_end <= hp_end) {
				scaled.add_LP_slot(sched.LP[i].t, f_lp);
				++i;
			}
			if (hp_end <= lp_end) {
				scaled.add_HP_slot(sched.HP[j].t, f_hp);
				++j;
			}
		}
	}
	while (i < sched.LP.size()) {
		scaled.add_LP_slot(sched.LP[i].t, f_lp);
		++i;
	}
	while (j < sched.HP.size()) {
		scaled.add_HP_slot(sched.HP[j].t, f_hp);
		++j;
	}
	return scaled;
}
