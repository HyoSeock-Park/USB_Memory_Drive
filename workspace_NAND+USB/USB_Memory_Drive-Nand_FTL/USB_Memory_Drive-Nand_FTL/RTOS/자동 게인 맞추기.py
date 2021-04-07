# d, v = map(int,input().split())
# wind = int(input())

d,v = 1,1
wind = 0.1
N = 100
time = d/v*N #[ms]단위 통신
target = 70
now = 45
nows = []
T = 0

gains = [1,0,0]

def Resonate(nows,n):
  global T
  data = nows[N-n:]
  data.reverse()
  # print(data)
  start_idx = 0

  for n_idx in range(start_idx+1,n):
    if data[n_idx] == data[start_idx]:
      T = n_idx - start_idx
      for j in range(T):
        if data[n_idx + j] != data[start_idx + j]:
          break
        return True
  return False


def f_error(gains):
  [kp, ki, kd] = gains
  global now, time
  I = 0
  error_pre = 0
  now_pre = now

  while time:
    error = target - now
    P = error
    I += error
    D = error_pre - error
    error_pre = error

    now = kp*P + ki*I + kd*D
    now = (now - now_pre)*(1-wind) + now_pre
    nows.append(now//1)
    now_pre = now
    time -= 1
  # print('now:',now,' error:',(target-now))
  # print(nows)
  return Resonate(nows,N//10)

def f_now(gains):
  [kp, ki, kd] = gains
  global now, time
  I = 0
  error_pre = 0
  now_pre = now

  while time:
    error = target - now
    P = error
    I += error
    D = error_pre - error
    error_pre = error

    now = kp*P + ki*I + kd*D
    now = (now - now_pre)*(1-wind) + now_pre

    now_pre = now
    time -= 1
  # print('now:',now,' error:',(target-now))

  return now


for i in range(0,2,1):
  i = i//10
  gains = [i,0,0]
  if f_error(gains):
    gains = [gains[0], 0.5*T, 0.125*T]
    now = f_now(gains)
    print('now:',now,' error[%]:',(target-now)/target*100)
    


# gains = [2,0,0]
# a = f_error(gains)
# print(a)
# print('now:',now,' error[%]:',(target-now)/target*100)
