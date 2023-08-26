#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

typedef	struct s_pipe
{
	int	value[2];
}		t_pipe;

t_pipe	*make_pipe()
{
	t_pipe *p;
    
	p = malloc(sizeof(t_pipe));

    // Create a pipe
    if (pipe(p->value) == -1) {
        perror("Pipe creation failed");
        exit(EXIT_FAILURE);
    }
	return p;
}

void make_test(int pipe[2], int value, int r)
{
    pid_t child_pid = fork();
    
    if (child_pid == -1) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }
    
    if (child_pid == 0) {
        // Child process
        
        close(pipe[1]); // Close the write end of the pipe
        
        char buffer[70];
		ssize_t bytes_read;
		if (r)
			bytes_read = read(pipe[0], buffer, 50);
        else 
			bytes_read = 0;
        // = 
        if (bytes_read > 0) {
            printf("%d\tChild received: %.*s\n", value, (int)bytes_read, buffer);
        }
		if (r)
			bytes_read = read(pipe[0], buffer, 50);
        else 
			bytes_read = 0;
        // = 
        if (bytes_read > 0) {
            printf("%d\tChild received: %.*s\n", value, (int)bytes_read, buffer);
        }
        
        close(pipe[0]); // Close the read end of the pipe
		exit(EXIT_SUCCESS);
    } else {
        // Parent process
        
        close(pipe[0]); // Close the read end of the pipe
        
        char message[] = "Hello from parent!";
        ssize_t bytes_written = write(pipe[1], message, sizeof(message));
        
        if (bytes_written > 0) {
            printf("%d\tParent sent: %s\n", value, message);
        }
        
        close(pipe[1]); // Close the write end of the pipe
        
        wait(NULL); // Wait for the child to finish
        
    }
}

int main() {
	int		pup[2];
	t_pipe	*p = make_pipe();
    
	make_test(p->value,1, 0);
	printf("-----\n");
	pipe(pup);
	make_test(pup, 2, 0);
	printf("-----\n");
	p = make_pipe();
    make_test(p->value, 3,0);
	pipe(pup);
	printf("-----\n");
	make_test(pup, 4,1);
    return 0;
}