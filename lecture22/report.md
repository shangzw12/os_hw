###����ļ����ʵ�ִ�й���

����ΰ 2012011366

��ע��˼·�ο��߲�ͬѧʵ��


����ͨ��understand��̬����������õ����µĵ��ù�ϵ
sys_read=>sysfile_read=>file_read
Ȼ����file_read������understand����ʱ����û���ҵ����Ե��ļ���ȡ����
�ҵ�file_read�����Ķ���(file.c)������һ���궨���vop_read

	*    vop_read        - Read data from file to uio, at offset specified
	*                      in the uio, updating uio_resid to reflect the
	*                      amount read, and updating uio_offset to match.
	*                      Not allowed on directories or symlinks.
	#define vop_read(node, iob)        (__vop_op(node, read)(node, iob))

չ������õ�inode->vop_read, �����inode��ʼ����ʱ����sfs_read
֮��sfs���õ�dop_io, ���õ���device�����io����, ������豸��io����, ����������ļ��Ķ��Ĺ���

�޸ĵ��ļ�����kern/fs/file.c, kern/fs/sysfile.c, kern/fs/sfs/sfs_io.c, kern/fs/sfs/sfs_inode.c, kern/fs/devs/dev_disk0.c, kern/driver/ide.c

�����

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
���Կ���������ĵ��ù�����:
syscall => sysfile_read => file_read => vop_read => sfs_io => sfs_io_nolock => sfs_rbuf / sfs_rblock->sfs_rwblock => sfs_rwblock_nolock => disk0_io => disk0_read_blks_nolock => ide_read_secs => insl
