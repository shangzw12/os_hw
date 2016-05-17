###理解文件访问的执行过程

尚智伟 2012011366

！注：思路参考高博同学实现


首先通过understand静态代码分析，得到大致的调用关系
sys_read=>sysfile_read=>file_read
然而在file_read函数用understand分析时，并没有找到明显的文件读取函数
找到file_read函数的定义(file.c)，发现一个宏定义的vop_read

	*    vop_read        - Read data from file to uio, at offset specified
	*                      in the uio, updating uio_resid to reflect the
	*                      amount read, and updating uio_offset to match.
	*                      Not allowed on directories or symlinks.
	#define vop_read(node, iob)        (__vop_op(node, read)(node, iob))

展开后调用到inode->vop_read, 这个在inode初始化的时候导向sfs_read
之后sfs调用到dop_io, 调用的是device对象的io函数, 这个是设备的io操作, 最后就完成了文件的读的过程

修改的文件包括kern/fs/file.c, kern/fs/sysfile.c, kern/fs/sfs/sfs_io.c, kern/fs/sfs/sfs_inode.c, kern/fs/devs/dev_disk0.c, kern/driver/ide.c

输出：

	sysfile_read begin
	file_read begin
	file_read file acquired
	vop_read(sfs_read) begin
	sfs_io begin
		sfs_io_nolock begin
		sfs_io_nolock begin reading (by sfs_rblock or sfs_rbuf)
			sfs_rbuf begin
			sfs_rwblock_nolock begin
			sfs_rwblock_nolock iobuf_init
				disk0_io begin
				disk0_read_blks_nolock begin
					ide_read_secs begin
					ide_read_secs call insl to read from disk
					ide_read_secs end
				disk0_read_blks_nolock end
				disk0_io end
			sfs_rwblock_nolock end
			sfs_rbuf end
		sfs_io_nolock end
	sfs_io end
	file_read file released
	file_read end
	sysfile_read end
可以看出，具体的调用过程是:
syscall => sysfile_read => file_read => vop_read => sfs_io => sfs_io_nolock => sfs_rbuf / sfs_rblock->sfs_rwblock => sfs_rwblock_nolock => disk0_io => disk0_read_blks_nolock => ide_read_secs => insl
