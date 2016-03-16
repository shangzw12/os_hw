def read_data():
	raw_data = input("Please input v_addr: ")
	data = raw_data
	print(data)
	return data

def read_file(filename):
	obj = open(filename)
	mem = {}
	data = obj.read()
	data = data.split('\n')
	for data_row in data:
		row = data_row.split(' ')
		if (row == ['']):
			continue
		ID = row[1]
		mem[int(ID[0:2],16)] = row[2:33] 
	return mem

def addr_convert(v_addr, mem, disk):
	bin_v_addr = format(int(v_addr, 16),'015b')
	pde_id = int(bin_v_addr[0:5], 2) 
	pte_id = int(bin_v_addr[5:10], 2)
	offset = int(bin_v_addr[10:15], 2)
	base_addr = int("0xd80", 16)
	pde_addr = format(pde_id + base_addr,'012b')
	pfn = mem[int(pde_addr[0:7],2)][int(pde_addr[7:12],2)]
	pfn = format(int(pfn, 16), '08b')
	valid_pfn = pfn[0:1]
	print ("pde_index: "+ str(hex(pde_id)))
	print ("pde_content: "+ str(pfn)+ "  valid: "+ str(valid_pfn)+"  pfn: "+str(hex(int(pfn[1:8], 2))))
	if( not eval(valid_pfn)):
		print("Fault!")
		return 
	pte_base_addr = pfn[1:8]
	#print("pte_addr: "+ str(pte_addr))
	#print(str(pte_base_addr))
	ptn = mem[int(pte_base_addr,2)][pte_id]
	ptn = format(int(ptn, 16), '08b')
	valid_ptn = ptn[0:1]
	print ("pte_index: "+ str(hex(pte_id)))
	print ("pte_content: "+ str(ptn)+ "  valid: "+ str(valid_ptn)+"  ptn: "+str(hex(int(ptn[1:8], 2))))
	if(not eval(valid_ptn)):
		print("Fault! Search in disk!")
		value = disk[int(ptn[1:8], 2)][offset]
		print ("--> value: 0x"+ str(value))
		return
	value = mem[int(str(ptn[1:8]), 2)][offset]
	print ("--> value: 0x"+ str(value))
	
def my_func():
	mem = read_file('table')
	#print (mem)
	disk = read_file('disk')
	#print (disk)
	v_addr = read_data()
	addr_convert(v_addr, mem, disk)

my_func()
# 按照题目中的地址格式输入即可
	
	