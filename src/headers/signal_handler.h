/**
 * @file signal_handler.h
 * @author David Cuenca Marcos
 * @brief Signal hadler program.
 * @version 0.1
 * @date 2021-05-06
 * 
 * @copyright Copyright (c) 2021
 * 
 */

/**
 * @brief Signal handler for signint. Mostly for parent process.
 * 
 * @param sig Signal :=)
 */
void signint_parent(int sig);

/**
 * @brief Signal handler for signint. Mostly for child process.
 * 
 * @param sig Signal :=)
 */
void signint_child(int sig);

/**
 * @brief Signal handler for signstp.
 * 
 * @param sig Signal :=)
 */
void signstp(int sig);