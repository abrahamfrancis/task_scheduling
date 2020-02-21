#include "schedule.hpp"

schedule contingency_schedule(const schedule &sched) {
	schedule cs;
	auto add_cslot = [&cs](task a, task b) {
		cs.add_LP_slot(a);
		cs.hp_time = cs.lp_time - a.size();
		cs.add_HP_slot(b);
	};
	auto task_bar = [](task t) {
		return task(2*MAX_TASKs - 1 - t.get_id(), t.size(), t.lp_size(), t.get_a_LP(), t.get_alpha_LP());
	};
	double total_lp_time = 0.0;
	for (const slot &s : sched.LP) {
		total_lp_time += s.t.lp_size();
	}
	for (const slot &s : sched.HP) {
		total_lp_time += s.t.lp_size();
	}
	double offset = MAX_DUR - total_lp_time;
	cs.lp_time = cs.hp_time = offset;
	unsigned int i = 0, j = 0;
	while (i < sched.LP.size() && j < sched.HP.size()) {
		double lp_end = sched.LP[i].start + sched.LP[i].t.lp_size(),
		       hp_end = sched.HP[j].start + sched.HP[j].t.size();
		if (std::abs(sched.HP[j].start - lp_end) <= delta) {
			task t = sched.LP[i].t;
			task t_bar = task_bar(t);
			add_cslot(t, t_bar);
			++i;
		} else if (std::abs(sched.LP[i].start - hp_end) <= delta) {
			task t = sched.HP[j].t;
			task t_bar = task_bar(t);
			add_cslot(t_bar, t);
			++j;
		} else if (std::abs(sched.LP[i].start - sched.HP[j].start) <= delta) {
			if (lp_end >= hp_end) {
				task t = sched.LP[i].t;
				task t_bar = task_bar(t);
				add_cslot(t, t_bar);
				++i;
			}
			if (hp_end >= lp_end) {
				task t = sched.HP[j].t;
				task t_bar = task_bar(t);
				add_cslot(t_bar, t);
				++j;
			}
		} else {
			if (sched.LP[i].start <= sched.HP[j].start) {
				task t = sched.LP[i].t;
				task t_bar = task_bar(t);
				add_cslot(t, t_bar);
				++i;
			} else {
				task t = sched.HP[j].t;
				task t_bar = task_bar(t);
				add_cslot(t_bar, t);
				++j;
			}
		}
	}
	while (i < sched.LP.size()) {
		task t = sched.LP[i].t;
		task t_bar = task_bar(t);
		add_cslot(t, t_bar);
		++i;
	}
	while (j < sched.HP.size()) {
		task t = sched.HP[j].t;
		task t_bar = task_bar(t);
		add_cslot(t_bar, t);
		++j;
	}
	return cs;
}
