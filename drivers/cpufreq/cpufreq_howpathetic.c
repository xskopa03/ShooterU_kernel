/*
 *  Copyright (C) 2014 Jakub Skopal <jakub.skopal1@gmail.com>
 *
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 */

static int cpufreq_governor_powersave(struct cpufreq_policy *policy, unsigned int event) {
	pr_debug("HOWPATHETIC: Event: %u", event);

	switch (event) {
		case CPUFREQ_GOV_START:
			break;
		case CPUFRQ_GOV_STOP:
			break;
		case CPUFREQ_GOV_LIMITS:
			pr_debug("HOWPATHETIC: Setting to %u kHz because of event %u\n", policy->min, event);
			__cpufreq_driver_target(policy, policy->min, CPUFREQ_RELATION_L);
		break;
		default:
			break;
	}

	return 0;
}

#ifndef CONFIG_CPU_FREQ_DEFAULT_GOV_HOWPATHETIC
static
#endif
struct cpufreq_governor cpufreq_gov_howpathetic = {
	.name		= "howpathetic",
	.governor	= cpufreq_governor_howpathetic,
	.owner		= THIS_MODULE,
};

static int __init cpufreq_gov_howpathetic_init(void) {
	return cpufreq_register_governor(&cpufreq_gov_howpathetic);
}


static void __exit cpufreq_gov_howpathetic_exit(void) {
	cpufreq_unregister_governor(&cpufreq_gov_howpathetic);
}

MODULE_AUTHOR("Jakub Skopal <jakub.skopal1@gmail.com>");
MODULE_DESCRIPTION("CPUfreq policy governor 'howpathetic'");
MODULE_LICENSE("GPL");

#ifdef CONFIG_CPU_FREQ_DEFAULT_GOV_HOWPATHETIC
fs_initcall(cpufreq_gov_howpathetic_init);
#else
module_init(cpufreq_gov_howpathetic_init);
#endif
module_exit(cpufreq_gov_howpathetic_exit);