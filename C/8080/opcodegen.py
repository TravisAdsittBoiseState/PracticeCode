
prefix = '00'

registers = {'111','000','001','010','011','100','101'}
rp = {'00','01','10','11'}
#for r in registers:
#	print("\t\tcase "+str(hex(int(prefix + r + '110',2))) + ':')

prefix = '01'

#for r1 in registers:
#	for r2 in registers:
#		print("\t\tcase " + str(hex(int(prefix + r1 + r2,2))) + ':')

#for r in registers:
#	print("\t\tcase "+str(hex(int(prefix +'110'+ r,2))) + ':')
			
#for r in registers:
#	print("\t\tcase "+str(hex(int(prefix + r + '110',2))) + ':')

prefix = '00'

#for r in rp:
#	print("\t\tcase "+str(hex(int(prefix + r + '0010',2))) + ':')

prefix = '10'

for r in registers:
	print("\t\tcase "+str(hex(int(prefix + '111' + r,2))) + ':')

prefix = '00'

#for r in registers:
#	print("\t\tcase "+str(hex(int(prefix + r + '101',2))) + ':')

#for r in rp:
#	print("\t\tcase "+str(hex(int(prefix + r + '1001',2))) + ':')
				
