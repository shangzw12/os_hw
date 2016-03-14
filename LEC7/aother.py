
def translate(str):
    va = str.strip().split()[1][:-1]
    pa = str.strip().split()[3]
    pde_idx = eval(bin(eval(va[:5]))[:-2])#str
    pde_ctx = (pde_idx-0x300+1)*2**12+3
    pte_idx = eval('0b'+bin(eval(va))[-22:-12])#str
    pte_ctx = eval(pa[:-3])*2**12+3
    
    print ('va %s, pa %s, pde_idx 0x%08x, pde_ctx 0x%08x, pte_idx 0x%08x, pte_ctx 0x%08x'%(va,pa,pde_idx,pde_ctx,pte_idx,pte_ctx))

if __name__=='__main__':
    translate('va 0xcd82c07c, pa 0x0c20907c')
    translate('va 0xc2265b1f, pa 0x0d8f1b1f')
    translate('va 0xcc386bbc, pa 0x0414cbbc')
    translate('va 0xc7ed4d57, pa 0x07311d57')
    translate('va 0xca6cecc0, pa 0x0c9e9cc0')
    translate('va 0xc18072e8, pa 0x007412e8')
    translate('va 0xcd5f4b3a, pa 0x06ec9b3a')
    translate('va 0xcc324c99, pa 0x0008ac99')
    translate('va 0xc7204e52, pa 0x0b8b6e52')
    translate('va 0xc3a90293, pa 0x0f1fd293')
    translate('va 0xce6c3f32, pa 0x007d4f32')