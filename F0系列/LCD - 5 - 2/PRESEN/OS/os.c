#include "os.h"
#define SUCCESS 1
#define FAILURE 0
/************************************************
函数名称 ： OS_Init
功    能 ： 对任务列表初始化
参    数 ： 无
返 回 值 ： 无
*************************************************/
void OS_Init(void)
{
	u8 i;
	for(i = 0;i < OS_STASK_MAX; i++)
	{
		OS_Delete_Task(i);
	}
}

/************************************************
函数名称 ： OS_Delete_Task
功    能 ： 删除任务
参    数 ： 任务标号
返 回 值 ： 无
*************************************************/
void OS_Delete_Task(u8 TASK_INDEX)
{
}

typedef enum {
  ERROR1,
  DOOR_IS_CLOSED,
  DOOR_IS_OPEN,
  NB_STATES
} state_t;

/**
 * Define the events
 */
typedef enum {
  OPEN_DOOR,
  CLOSE_DOOR,
  NB_EVENTS
} event_t;

/**
 * Define the "look/feel" of what an action is.
 */
typedef int (* action_t) (void);

/**
 * Known actions
 */
static int nothing(void)
{
  return SUCCESS;
}

static int open_the_door(void)
{

}

static int close_the_door(void)
{

}

/**
 * Define the actions to take
 * STATE x EVENT -> ACTION
 */
static const action_t actions[NB_STATES][NB_EVENTS] = {
  [ERROR1] = {
    [OPEN_DOOR] = nothing,
    [CLOSE_DOOR] = nothing,
  },
  [DOOR_IS_CLOSED] = {
    [OPEN_DOOR] = open_the_door,
    [CLOSE_DOOR] = nothing,
  },
  [DOOR_IS_OPEN] = {
    [OPEN_DOOR] = nothing,
    [CLOSE_DOOR] = close_the_door
  }
};

/**
 * Define transitions between states
 *
 * STATE x EVENT -> STATE
 */
static const state_t transitions[NB_STATES][NB_EVENTS] = {
  [ERROR] = {
    [OPEN_DOOR] = ERROR1,
    [CLOSE_DOOR] = ERROR1,
  },
  [DOOR_IS_CLOSED] = {
    [OPEN_DOOR] = DOOR_IS_OPEN,
    [CLOSE_DOOR] = DOOR_IS_CLOSED,
  },
  [DOOR_IS_OPEN] = {
    [OPEN_DOOR] = DOOR_IS_OPEN,
    [CLOSE_DOOR] = DOOR_IS_CLOSED
  }
};

/**
 * State-machine execution
 */
static void state_machine(event_t event)
{
  static state_t current_state = DOOR_IS_CLOSED;

  const action_t action = actions[current_state][event];

  const int status = action ? action() : FAILURE;
  const state_t new_state = (status == SUCCESS) ? transitions[current_state][event] : ERROR1;

  // TODO: possibility to do pre/post state actions

  current_state = new_state;
}
