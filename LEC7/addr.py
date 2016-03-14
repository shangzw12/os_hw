def read_data():
	raw_data = input("Please input v_addr and P_addr: ")
	data = raw_data.split(', ')
	v_addr = (data[0].split(' '))[1]
	p_addr = (data[1].split(' '))[1]
	data = {'v_addr': v_addr, 'p_addr': p_addr}
	print(data)
	return data

def translate(v_addr, p_addr):
	bin_v_addr = format(int(v_addr, 16),'032b')
	pde_id = int(bin_v_addr[0:10], 2) 
	pte_id = int(bin_v_addr[10:20], 2) 
	ptn = (int(p_addr[3: 7], 16))<< 12 |0x03 
	pfn = (pde_id - int('0x300',16) +1)<< 12 |0x03
	print ('va %s, pa %s, pde_idx 0x%08x, pde_ctx 0x%08x, pte_idx 0x%08x, pte_ctx 0x%08x'
	%(v_addr,p_addr,pde_id,pfn,pte_id,ptn))

def my_func():
	data = read_data()
	translate(data['v_addr'], data['p_addr'])

my_func()
# 按照题目中的地址格式输入即可
	
	