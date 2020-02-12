#include "schedule.hpp"

schedule schedule::uniform_scale() {
	double f_lp = 0.65, f_hp = 0.81;
	schedule scaled;
	unsigned int i = 0, j = 0;
	while (i < this->LP.size() && j < this->HP.size()) {
		double lp_end = LP[i].start + LP[i].t.lp_size(),
				hp_end = HP[j].start + HP[j].t.size();
		if (std::abs(HP[j].start - lp_end) <= delta) {
			scaled.add_LP_slot(LP[i].t, f_lp);
			scaled.wait();
			++i;
		} else if (std::abs(LP[i].start - hp_end) <= delta) {
			scaled.add_HP_slot(HP[j].t, f_hp);
			scaled.wait();
			++j;
		} else {
			if (lp_end <= hp_end) {
				scaled.add_LP_slot(LP[i].t, f_lp);
				++i;
			}
			if (hp_end <= lp_end) {
				scaled.add_HP_slot(HP[j].t, f_hp);
				++j;
			}
		}
	}
	while (i < this->LP.size()) {
		scaled.add_LP_slot(LP[i].t, f_lp);
		++i;
	}
	while (j < this->HP.size()) {
		scaled.add_HP_slot(HP[j].t, f_hp);
		++j;
	}
	return scaled;
}
