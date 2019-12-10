//sudo mknod -m 666 /dev/my_device c 240 0
//make && insmod my_driver.ko && ./testDrive
//rmmod my_driver.ko

#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

MODULE_LICENSE("Dual BSD/GPL");

char message[256];
char aux[256];
static short msgLen;
int grafo[10][10];
int adj[10];
int i, j, k, error_count;

void inserir(int grafo[][10], int verticeI, int verticeJ){
	grafo[verticeI][verticeJ] = 1;
	grafo[verticeJ][verticeI] = 1;
	printk("%d%s", grafo[verticeI][verticeJ], "\n");
	return;
}

void remover(int grafo[][10], int verticeI){
	for (j = 0; j < 10; j++)
		grafo[verticeI][j] = 0;	

	
	for (i = 0; i < 10; i++)
		grafo[i][verticeI] = 0;

	i = 0;
	j = 0;

	return;
}

void buscar(int grafo[][10], int adj[10], int verticeI){
	printk("Adjacente a: \n");
	for (j = 0; j < 10; j++){
		if (grafo[verticeI][j] == 1){
			adj[k] = j;
			printk("%d", j);
			k++;
		}		
	}	

	k = 0;
	j = 0;
	return;
}

ssize_t my_driver_read (struct file *dfile, char __user *buffer , size_t length , loff_t *offset){
	printk(KERN_ALERT "Inside the %s function\n", __FUNCTION__);	

	error_count = 0;
	error_count = copy_to_user(buffer, message, msgLen);
	

	if (error_count == 0){
		printk(KERN_INFO "Operacao bem sucedida\n");
		return (msgLen = 0);
	}
	else{
		printk(KERN_INFO "Falha\n");
		return -EFAULT;
	}

	printk(KERN_ALERT "Inside the %s function\n", __FUNCTION__);
	return 0;
}

ssize_t my_driver_write (struct file *dfile, const char __user *buffer, size_t length, loff_t *offset){
	k = 0;
	printk(KERN_ALERT "Inside the %s function\n", __FUNCTION__);
	
	if (buffer[0] == 'i' && buffer[1] == ' '){
		inserir(grafo, (int)buffer[2] - 48, buffer[5] - 48);
		printk(KERN_ALERT "%s%d%s%d%s", "Inserida aresta entre o vertice ", buffer[2] - 48, " e ", buffer[5] - 48, "\n");
		sprintf(message,"Inserido com sucesso!\n");		
		msgLen = strlen(message);
		k++;
	}

	else if (buffer[0] == 'r' && buffer[1] == ' '){
		remover(grafo, buffer[2] - 48);
		printk(KERN_ALERT "%s%d%s%d%s", "Removida a aresta entre o vertice ", buffer[2] - 48, " e ", buffer[5] - 48, "\n");
		sprintf(message,"Removido com sucesso!\n");
		msgLen = strlen(message);
		k++;
	}
	
	else if (buffer[0] == 'b' && buffer[1] == ' '){
		buscar(grafo, adj, buffer[2] - 48);
		sprintf(message,"Buscado com sucesso!\n");
		msgLen = strlen(message);
		k++;
	}

	if (k == 0){
		sprintf(message,"ENTRADA INVALIDA!\n");
		msgLen = strlen(message);
	}

	k = 0;
	
	return length;	
}

int my_driver_open (struct inode *dinode , struct file *dfile ){
	printk(KERN_ALERT "Inside the %s function\n", __FUNCTION__);
	for (i = 0; i < 10; i++){
        for (j = 0; j < 10; j++){
            grafo[i][j] = 0;
        }
        adj[i] = 0;
    }

    i = 0;
    j = 0;
    return 0;
}

int my_driver_close (struct inode *dinode ,  struct file *dfile){
	printk(KERN_ALERT "Inside the %s function\n", __FUNCTION__);
    return 0;
}


struct file_operations my_driver_file_operations = {
	.owner = THIS_MODULE,
	.open = my_driver_open,
	.read = my_driver_read,
	.write = my_driver_write,
	.release = my_driver_close,
};
	


static int my_driver_init(void){
 	register_chrdev(240, "my_driver", &my_driver_file_operations);
 	printk(KERN_ALERT "Hello, world\n");
 	return 0;
}

static void my_driver_exit(void){
	printk(KERN_ALERT "Goodbye, cruel world\n");
 	unregister_chrdev(240, "my_driver");
}




module_init(my_driver_init);
module_exit(my_driver_exit);
