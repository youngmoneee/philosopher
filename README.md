# Philosopher

1. 1 to N명의 철학자가 원탁에서 식사
2. 철학자는 먹거나 생각하거나, 잠자기 가능
	- 밥먹는 동안은 생각, 잠자지 않음. 다른 Job도 마찬가지
	- 식탁에 포크는 철학자 수만큼 존재
	- 철학자는 양손에 포크를 쥐고 식사함(Race Condition)
	- 철학자가 밥 다먹으면 포크를 내려놓고 잠자기 시작, 깨어나면 생각하기 시작함.
	- 해당 상황은 철학자가 기아 상태로 굶어 죽으면 종료됨.

3. 제약 조건
	- 철학자는 굶어죽으면 안됨
	- 철학자는 옆 사람이랑 대화 안함(IPC 쓰지 말라는건가?)
	- 철학자는 다른 철학자의 상태를 모름

4. 규칙
	- 프로그램은 
	{
		arguments : {
			철학자/포크의 수,
			굶어죽기까지 걸리는 시간,
			먹는데 걸리는 시간(포크 들고있는 상태),
			자는데 걸리는 시간
		}
		optional : 각 철학자가 필수로 먹어야 하는 횟수, 철학자가 죽거나 해당 횟수가 찼다면 종료
	}의 인자를 받음

	- 각 철학자는 1부터 N 까지의 수 중 자기 번호를 가짐, 1..2...N .. 1로 앉음
	- 철학자의 status가 변경될 때, 
	''' bash
	$> {timestamp}_in_ms X has taken a fork
	$> {timestamp}_in_ms X is eating
	$> {timestamp}_in_ms X is sleeping
	$> {timestamp}_in_ms X is thinking
	$> {timestamp}_in_ms X is died
	'''

	- 출력된 status는 다른 철학자의 status와 뒤섞일 수 없으며, 출력 오차 허용은 10ms 이내

5. pre-condition
	- Mandatory : 
		첧학자가 스레드로 존재, 철학자가 한 명이면 테이블에는 하나의 포크가 있어야 함
		포크가 복사되지 않도록, 포크를 뮤텍스로 관리

	- bonus :
		모든 포크는 테이블 중앙에 있으며, 사용 가능한 포크 수는 세마포어로 표현됨
		각 철학자는 프로세스이며, 메인 프로세스(Master Node)는 철학자가 아니어야 함

6. Forbidden
	Makefile, *.c, *.o, philo/, philo_bonus/
	Libft 금지

	- stdlib
	memset, printf, malloc, free, write, usleep, gettimeofday,
	
	-pthread
	pthread_create, pthread_detach, pthread_join, pthread_mutex_init,
	pthread_mutex_destroy, pthread_mutex_lock, pthread_mutex_unlock

	# bonus의 경우
	- 
	pthread_create, pthread_detach, pthread_join에 더불어
	sem_open, sem_close, sem_post, sem_wait, sem_unlink 사용 가능
