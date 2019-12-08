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

void inserir(int grafo[10][10], int verticeI, int verticeJ){
	grafo[verticeI][verticeJ] = 1;
	grafo[verticeJ][verticeI] = 1;
	return;
}

void remover(int grafo[10][10], int verticeI){
	for (j = 0; j < 10; j++)
		grafo[verticeI][j] = 0;	

	
	for (i = 0; i < 10; i++)
		grafo[i][verticeI] = 0;

	i = 0;
	j = 0;

	return;
}

void buscar(int grafo[10][10], int adj[10], int verticeI){
	for (j = 0; j < 10; j++){
		if (grafo[verticeI][j] == 1){
			adj[k] = j;
			printk("%d%c", k, ' ');
			k++;
		}
	}

	printk("\n");

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
	//i 1, 2
	if (buffer[0] == 'i'){
		inserir(grafo, (int)buffer[2], (int)buffer[5]);		
		sprintf(message,"Inserido com sucesso!\n");
		msgLen = strlen(message);
		k++;
	}
	//r 2
	else if (buffer[0] == 'r'){
		remover(grafo, (int)buffer[2]);
		sprintf(message,"Removido com sucesso!\n");
		msgLen = strlen(message);
		k++;
	}
	//b 2
	else if (buffer[0] == 'b'){
		buscar(grafo, adj, (int)buffer[2]);
		sprintf(message,"Buscado com sucesso!\n");
		msgLen = strlen(message);
		k++;
	}

	if (k == 0){
		sprintf(message,"ENTRADA INVALIDA!\n");
		msgLen = strlen(message);
	}

	k = 0;
	

	//printf(KERN_INFO, "Operacao realizada com sucesso!\n");



	
	//sprintf(message, "%s(%zu letters)", buffer, length);
	//msgLen = strlen(message);
	//printk(KERN_INFO "Recebidos %zu caracteres do usuario\n", length);
	return length;
	//printk(KERN_ALERT "Inside the %s function\n", __FUNCTION__);
	//return length;
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
