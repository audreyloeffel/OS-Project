/*
 * Dummy scheduling class, mapped to range of 5 levels of SCHED_NORMAL policy
 */

#include "sched.h"

/*
 * Timeslice and age threshold are repsented in jiffies. Default timeslice
 * is 100ms. Both parameters can be tuned from /proc/sys/kernel.
 */

#define DUMMY_TIMESLICE		(100 * HZ / 1000)
#define DUMMY_AGE_THRESHOLD	(3 * DUMMY_TIMESLICE)
#define NUMBER_PRIORITY 5
#define PRIO_OFFSET 11

unsigned int sysctl_sched_dummy_timeslice = DUMMY_TIMESLICE;
static inline unsigned int get_timeslice(void)
{
	return sysctl_sched_dummy_timeslice;
}

unsigned int sysctl_sched_dummy_age_threshold = DUMMY_AGE_THRESHOLD;
static inline unsigned int get_age_threshold(void)
{
	return sysctl_sched_dummy_age_threshold;
}

/*
 * Init
 */

void init_dummy_rq(struct dummy_rq *dummy_rq, struct rq *rq)
{
	//init all queues
	for(int i = 0; i++; i<NUMBER_PRIORITY({
		INIT_LIST_HEAD((&dummy_rq->queues)[i]); //je sais pas comment faire avec pointeur/adresse xD
	}
}

/*
 * Helper functions
 */

static inline struct task_struct *dummy_task_of(struct sched_dummy_entity *dummy_se)
{
	return container_of(dummy_se, struct task_struct, dummy_se);
}

static inline void _enqueue_task_dummy(struct list_head *queue, struct task_struct *p)
{
	
	
	
	//TODO : changer queue par la liste des queues ou dans l'autre fonction?
	//struct list_head *queues = &rq->dummy.queues;
	
	struct sched_dummy_entity *dummy_se = &p->dummy_se;
	struct task_struct *task = &dummy_se->run_list;
	&task.prio = &task.static_prio;	
	list_add_tail(task, queue);
}

static inline void _dequeue_task_dummy(struct task_struct *p)
{
	struct sched_dummy_entity *dummy_se = &p->dummy_se;
	list_del_init(&dummy_se->run_list);
}

/*
 * Scheduling class functions to implement
 */

static void enqueue_task_dummy(struct rq *rq, struct task_struct *p, int flags)
{
	long prio = p.prio-PRIO_OFFSET;
	struct list_head *queue = &rq->dummy.queues[prio];
	_enqueue_task_dummy(queue, p);
	add_nr_running(rq,1);
}

static void dequeue_task_dummy(struct rq *rq, struct task_struct *p, int flags)
{
	long prio = p.prio - PRIO_OFFSET;
	struct list_head *queue = &rq -> dummy.queues[prio];
	_dequeue_task_dummy(p);
	sub_nr_running(rq,1);
}

static void yield_task_dummy(struct rq *rq)
{
	_dequeue(rq->curr);
	_enqueue(rq->dummy_rq->queue[rq->curr.prio-PRIO_OFFSET], rq->curr)
	//resched rt.c ou fair.c
	set_tsk_need_resched(p);
}

static void check_preempt_curr_dummy(struct rq *rq, struct task_struct *p, int flags)
{
// s'il y a des taches dans les queues de plus grandes priorité que p, on enqueue p, et dequeue l'autre tache
	long prio = p.prio - PRIO_OFFSET; 
	if(rq->curr.prio > prio) {
		yield_task_dummy(rq);
	}
	
}

static struct task_struct *pick_next_task_dummy(struct rq *rq, struct task_struct* prev)
{
	struct dummy_rq *dummy_rq = &rq->dummy;
	struct sched_dummy_entity *next;
	
	if(!lists_empty(&dummy_rq->queues)) {
	
		//search the nonempty list with the higher priority
		int i = 0;
		while( list_empty((&dummy_rq->queues)[i]) && i<NUMBER_PRIORITY){
			i++;
		}
		next = list_first_entry((&dummy_rq->queues)[i], struct sched_dummy_entity, run_list);
                put_prev_task(rq, prev);
	

	return dummy_task_of(next);
	} else {
		return NULL;
	}
}
/*
Check if there is at least one non-empty list
*/
static int lists_empty(list_head lists[]){
	int ret = 1;
	for(int i = 0; i++; i<NUMBER_PRIORITY){
		if(!list_empty(lists[i]){
			ret = 0;
		}
	}
	return ret;
}

static void put_prev_task_dummy(struct rq *rq, struct task_struct *prev)
{
}

static void set_curr_task_dummy(struct rq *rq)
{
}

static void task_tick_dummy(struct rq *rq, struct task_struct *curr, int queued)
{
//appelé a chaque interrupt? ici aging et premption?
//tous les jiffies, yield
}

static void switched_from_dummy(struct rq *rq, struct task_struct *p)
{
}

static void switched_to_dummy(struct rq *rq, struct task_struct *p)
{
}

static void prio_changed_dummy(struct rq*rq, struct task_struct *p, int oldprio)
{
}

static unsigned int get_rr_interval_dummy(struct rq* rq, struct task_struct *p)
{
	return get_timeslice();
}
#ifdef CONFIG_SMP
/*
 * SMP related functions	
 */

static inline int select_task_rq_dummy(struct task_struct *p, int cpu, int sd_flags, int wake_flags)
{
	int new_cpu = smp_processor_id();
	
	return new_cpu; //set assigned CPU to zero
}


static void set_cpus_allowed_dummy(struct task_struct *p,  const struct cpumask *new_mask)
{
}
#endif
/*
 * Scheduling class
 */
static void update_curr_dummy(struct rq*rq)
{
}
const struct sched_class dummy_sched_class = {
	.next			= &idle_sched_class,
	.enqueue_task		= enqueue_task_dummy,
	.dequeue_task		= dequeue_task_dummy,
	.yield_task		= yield_task_dummy,

	.check_preempt_curr	= check_preempt_curr_dummy,
	
	.pick_next_task		= pick_next_task_dummy,
	.put_prev_task		= put_prev_task_dummy,

#ifdef CONFIG_SMP
	.select_task_rq		= select_task_rq_dummy,
	.set_cpus_allowed	= set_cpus_allowed_dummy,
#endif

	.set_curr_task		= set_curr_task_dummy,
	.task_tick		= task_tick_dummy,

	.switched_from		= switched_from_dummy,
	.switched_to		= switched_to_dummy,
	.prio_changed		= prio_changed_dummy,

	.get_rr_interval	= get_rr_interval_dummy,
	.update_curr		= update_curr_dummy,
};