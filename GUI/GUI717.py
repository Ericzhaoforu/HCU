import FreeSimpleGUI as sg #pip install FreeSimpleGUI
import time
import serial #pip install pyserial
import serial.tools.list_ports
import os
cur_path = os.getcwd()
cur_path+='\logo.png'
ports = []
hwids = []
serial_Name = ''
for port in serial.tools.list_ports.comports():
    hwids.append(port.hwid)
    hwid=str(port.hwid)
    if "PID=0403" in hwid:
        serial_Name = port.name
        #print(port.name)
        print("Detected Port {}".format(serial_Name))
if serial_Name =='':
    print("STM not found")
ser1 = serial.Serial(serial_Name, 115200)

print('Serial Port initialized')

debug = True
count = 0
in_process = False
process_timer = 0

def read_once(key = 'Y'):
    if ser1.in_waiting > 0:
        reade = str(ser1.read(ser1.in_waiting))
        for idx in range(len(reade)-1):
            if (key == reade[idx] and key == reade[idx+1]):
                return True
    return False

def read_loop(key = 'Y', time_out = 0):
    start = time.time()
    while True:
        if read_once(key = key):
            return True
        if time_out > 0 and (time.time() - start > time_out):
            return False      

sg.theme('Tan')   # Add a touch of color

#commands to STM32
button_names = {
    'Start': '1',
    'Stop': '2',
    'Reset': '3',
    'Large': '4',
    'Medium': '5',
    'Small': '6'
}

#formats
button_font = ['Helvetica', 20]
button_disable_color = ('lightgrey', 'Black')

button_format = {
    'size': (20,1),
    'font': button_font,
    'disabled_button_color': button_disable_color
}


#layout
col = [
    [sg.Image(cur_path,expand_x=True, expand_y=True )],
    [sg.Text('IF X RO+',font = ('Helvetica', 18))],
    [sg.Text('Choose the size of the package',font = ('Helvetica', 18))],
    [sg.Button('Small', button_color=('white','#DCEAF7'),**button_format),
     sg.Button('Medium', button_color=('white','#83CBEB'),**button_format),
     sg.Button('Large',  button_color=('white','#215F9A'),**button_format)]
    
]

col1 = [
    [sg.Text('Current process: ', size=(15,1),font = ('Helvetica', 18)), sg.Text(size=(20,1), font = ('Helvetica', 18),key='-ECHO-')],
    [sg.ProgressBar(30,size=(97,25), key='-PROGRESS_BAR-')]
]

layout = [sg.vbottom(
    [sg.Frame('', [[sg.Column(col, element_justification = 'center', vertical_alignment = 'center')],[sg.Column(col1, element_justification = 'left', vertical_alignment = 'center')]],element_justification = 'center', relief = 'flat',vertical_alignment='center')])
]

# Create the Window
window = sg.Window('IF X RO+', layout,  element_justification='center',use_ttk_buttons=True, element_padding = (10,5),location=(0,0), resizable=True)

def disable_all_button(): 
    for k in button_names.keys(): 
        if k in window.AllKeysDict:
            window[k].update(disabled=True)
    window.refresh()
        
def enable_all_button(): 
    for k in button_names.keys(): 
        if k in window.AllKeysDict:
            window[k].update(disabled=False)
    window.refresh()

def waiting_for_response():
    read1 = str(ser1.read(ser1.in_waiting))
    if read1 != '':
        print('STM32: ', read1)
        if read1 == 'M':
            print('read success')
            print('motor in position')
            window['-ECHO-'].update('Motor in position')
            in_process = True
    

# Event Loop to process "events" and get the "values" of the inputs
while True:
    print('---------------------------------')
    
    event, values = window.read()
    window['-ECHO-'].update('Ready')
    if event == (sg.WIN_CLOSED or 'Quit'): # if user closes window
        break

    elif 'Small' == event:
        ser1.write('A0200000'.encode())
        window['-ECHO-'].update('Small')
        print('Small')
        disable_all_button()
        while ser1.in_waiting == 0:
            pass
        #in_process = True
    
    elif 'Medium' == event:
        ser1.write('A0800000'.encode())
        window['-ECHO-'].update('Medium')
        print('Medium')
        disable_all_button()
        while ser1.in_waiting == 0:
            pass
        #in_process = True
    
    elif 'Large' == event:
        ser1.write('A2200000'.encode())
        window['-ECHO-'].update('Large')
        print('Large')
        disable_all_button()
        while ser1.in_waiting == 0:
            pass
        #in_process = True
    else:
        pass
    
    #print('Waiting for STM32 response')
    #time.sleep(0.2)

    #waiting_for_response()
    if ser1.in_waiting > 0:
        read1 = str(ser1.read(ser1.in_waiting))
        print('STM32: ', read1)
        if read1[2] == 'M':
            print('read success')
            print('motor in position')
            window['-ECHO-'].update('Motor in position')
            in_process = True
    
    # print('Waiting for process to complete')
    # print('in_process: ', in_process)

    if in_process:
        print('Movement started')
        disable_all_button()
        while process_timer < 30:
            print('Process timer: ', process_timer)
            process_timer += 1
            window['-PROGRESS_BAR-'].update(current_count=process_timer)
            time.sleep(0.4)
        in_process = False
        process_timer = 0
        window['-PROGRESS_BAR-'].update(current_count=0)
        window['-ECHO-'].update('Process completed')
        enable_all_button()
        print('Process completed')

window.close()
ser1.close()





