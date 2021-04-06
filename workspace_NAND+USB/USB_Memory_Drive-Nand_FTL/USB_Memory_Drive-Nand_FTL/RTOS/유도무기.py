# d, v = map(int,input().split())
# wind = int(input())

d,v = 1,1
wind = 0.1

time = d/v*100 #[ms]단위 통신
target = 70
now = 45
I = 0
error_pre = 0
now_pre = now

kp, ki, kd = 1.8,0,0
kp, ki, kd = 1.8*0.6,1,0.25
# kp, ki, kd = 0.6,1,0.25

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

print('now:',now,' error[%]:',(target-now)/target*100)
