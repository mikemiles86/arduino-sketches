import serial

ser = serial.Serial('/dev/ttyACM0',9600)
ser.open()

quit_program = False

while not quit_program:
  prompt = 'Type your command:'
  my_command = raw_input(prompt).strip()
  if my_command == 'QUIT':
    quit_program = False
  elif ser.isOpen():
    if ser.write(my_command):
      print 'command sent'
  else:
    print 'serial busy. try again.'

    