#include "schedule.hpp"

schedule uniform_scale(const schedule &sched, const schedule &sched_cs) {
	auto scale_freq = [] (const std::vector<slot> &s, const std::vector<slot> &cs, char mode) {
		double S, S_max=0.0;
		for (int i = 0, j = 0; i < s.size() && j < cs.size(); ++i) {
			while (j < cs.size() && cs[j].t.get_id() + s[i].t.get_id() + 1 != 2*MAX_TASKs) ++j;
			double size = (mode == 'H' ? s[i].t.size() : s[i].t.lp_size());
			S = (s[i].start + size) / cs[j].start;
			if (S > S_max) S_max = S;
		}
		return S_max;
	};
	double f_lp, f_hp,
	       S = std::max(scale_freq(sched.LP, sched_cs.HP, 'L'), scale_freq(sched.HP, sched_cs.LP, 'H'));
	if (S > 1.0) S = 1.0;
	f_lp = S*f_LP_max;
	f_hp = S*f_HP_max;
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
	if   (scaled.energy() > sched.energy()) return sched;
	else                                    return scaled;
}
