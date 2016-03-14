def read_data(filename):
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
	return data	
	
def addr_convert(addr, mem ): #str bin 15 bits
	pde_id = int( addr[0:5], 2 )
	pte_id = int( addr[5:10], 2 )
	offset  = addr[10:15]
	base_addr = int('0x220', 16)
	pde_ctn = mem[int('11', 16)][pde_id]
	bin_pde_ctn = bin(int(pde_ctn, 16))
	valid_pde = "1"
	if(len(bin_pde_ctn)< 10):
		valid_pde = "0"
		pfn = bin_pde_ctn[2: len(bin_pde_ctn)]
	else:
		pfn = bin_pde_ctn[3: len(bin_pde_ctn)]
	pte_ctn = str(bin(int(mem[int(pfn,2)][pte_id],16)))
	valid_pte = "1"
	if(len(pte_ctn)< 10):
		valid_pte = "0"
		ptn = pte_ctn[2: len(pte_ctn)]
	else:
		ptn = pte_ctn[3: len(pte_ctn)]
	print("-->pde index : "+str(hex(pde_id))+"    pde_contents: (valid = "+valid_pde+" pfn = "+str(hex(int(pfn, 2)))+")")
	print(" -->pte index : "+str(hex(pte_id))+"    pte_contents: (valid = "+valid_pte+" pfn = "+str(hex(int(ptn, 2)))+")")
	if(valid_pde == "1" and valid_pte == "1"):
		phy_addr = str(hex(int(ptn,2)*32 + int(offset, 2)))
		value = mem[int(ptn, 2)][int(offset, 2)]
		print("   --> Translates to physical address : "+phy_addr+" --> value : "+value)
	else:
		print("virtual address invalid!")	
	
def my_func(): 
  addr = input('please input a virtual address: ')
  addr = str(bin(int(addr, 16)))
  #print(addr)
  addr = addr[2:len(addr)]
  #print(addr)
  addr = ("000000000000000"+ addr)
  addr = addr[len(addr)-15:len(addr)]
  print (addr)
  mem = read_data('mem')
  addr_convert(addr, mem)

my_func();

'''
print read_data('mem');
'''
  
  
  