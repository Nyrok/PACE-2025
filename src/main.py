import sys
import signal

#https://www.optil.io/optilion/help/signals#python3
class Killer:
  exit_now = False
  def __init__(self):
    signal.signal(signal.SIGINT, self.exit)
    signal.signal(signal.SIGTERM, self.exit)

  #put the boolean to true on SIGTERM
  def exit(self,signum, frame):
    self.exit_now = True

killer = Killer()

#read the graph from stdin
for line in sys.stdin:
    print(line.strip())


'''

#demo of capturing SIGTERM
#to see how it works, run:
#timeout 1 python3 main.py < instance.gr
#exit_now is True after 1 second (in the benchmark, it will be after 5 minutes)
while True:
    #infinite loop unless the boolean is set to true (for demonstration purpose)
    #the boolean will be set to true upon capturing SIGTERM
    #note : timeout sends SIGTERM
    if killer.exit_now:
        break

'''

print("fin", file=sys.stderr)