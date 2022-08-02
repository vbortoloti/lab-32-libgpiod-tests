#include <gpiod.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>


#ifndef	CONSUMER
#define	CONSUMER	"Consumer"
#endif

float toDuty(int degree){
    float result = (float)degree/18;
    return result+ 2;

}

int main(int argc, char **argv)
{
	int degrees;
    if(argc == 1){
        printf("ERROR: INVALID INPUT - No arguments");
        return -1;
    }else if(argc > 2){
        printf("ERROR: INVALID INPUT - No arguments");

    }
    
    switch (argc)
    {
    case 1:
        printf("ERROR: INVALID INPUT - No arguments");
        return -1;
    break;

    case 2:
        degrees = strtol(argv[1], NULL, 10);
        if(degrees <0 || degrees > 180){
            printf("ERROR: INVALID INPUT - Please, enter a number between 0 and 180 degrees");
            return -1;
        }
        printf("Degrees: %d\n",degrees);

    
    break;

    default:
        printf("ERROR: INVALID INPUT - Too many arguments");
        return -1;
    }
    
    //VARIÁVEIS RELACIONADAS AO LIBGPIOD
	char *chipname = "gpiochip0";
	unsigned int line_num = 64;	// GPIO Pin #23
	struct gpiod_chip *chip;
	struct gpiod_line *line;
	int ret; unsigned int val;

	chip = gpiod_chip_open_by_name(chipname);
	if (!chip) {
		perror("Open chip failed\n");
		goto end;
	}

	line = gpiod_chip_get_line(chip, line_num);
	if (!line) {
		perror("Get line failed\n");
		goto close_chip;
	}

	ret = gpiod_line_request_output(line, CONSUMER, 0);
	if (ret < 0) {
		perror("Request line as output failed\n");
		goto release_line;
	}


	int frequency = 50;
	float duty = 7.0;
	double timespent,duty_up,duty_down, period, real_duty_up, real_duty_down;

	clock_t begin, end, begin_t, end_t;

	val = 1;
    period = (1/(double)frequency);

	//printf("GRAUS: %d\n ", degrees);

	duty = toDuty(degrees);

	//variáveis para teste
	duty_up = (period/100)*(double)duty;
	duty_down = period-duty_up;
	printf("Up:%f, down:%f\n", duty_up, duty_down);

	begin_t = clock();
	begin = clock();

	while((double)(end_t-begin_t)/CLOCKS_PER_SEC <= 20*period){
		//MODIFICANDO VALOR NO PINO
		ret = gpiod_line_set_value(line, val);
		if (ret < 0) {
			perror("Set line output failed\n");
			goto release_line;
		}

		//ATUALIZANDO CLOCK
		end_t = clock();
		end = clock();

		//CHECANDO SE JÁ PASSOU O TEMPO SUFICIENTE
		if(val ==1){
			timespent = (double)(end-begin)/CLOCKS_PER_SEC;
			if(timespent >= duty_up){
				real_duty_up = timespent;
				val = 0;
				begin = clock();
			}
		}else{
			timespent = (double)(end-begin)/CLOCKS_PER_SEC;

			if(timespent >= duty_down){
				real_duty_down = timespent;
				val = 1;
				begin = clock();
			}
		}


	}

	printf("Up:%f, down:%f\n", real_duty_up, real_duty_down);


    release_line:
        gpiod_line_release(line);
    close_chip:
        gpiod_chip_close(chip);
    end:

	return 0;
}
