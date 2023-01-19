#include <Arduino.h>

TaskHandle_t task1Handle = NULL;
TaskHandle_t task2Handle = NULL;

void task1Function(void *pvParameters) {
    while (1) {
        // Código para ser executado pela tarefa 1
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        Serial.println("Tarefa 1 Executando...");
    }
}

void task2Function(void *pvParameters) {
    while (1) {
        // Código para ser executado pela tarefa 2
        vTaskDelay(500 / portTICK_PERIOD_MS);
        Serial.println("Tarefa 2 Executando...");
    }
}

void setup() {
    Serial.begin(115200); // Inicializa a comunicação serial
    xTaskCreate(task1Function, "Task1", configMINIMAL_STACK_SIZE, NULL, 1, &task1Handle);
    xTaskCreate(task2Function, "Task2", configMINIMAL_STACK_SIZE, NULL, 1, &task2Handle);
}

void loop() {
    if (Serial.available()) {
        char command = Serial.read();

        if (command == '1') {
            vTaskSuspend(task1Handle); // Suspende a tarefa 1
            Serial.println("Tarefa 1 Suspensa");
        } else if (command == '2') {
            vTaskSuspend(task2Handle); // Suspende a tarefa 2
            Serial.println("Tarefa 2 Suspensa");
        } else if (command == '3') {
            vTaskResume(task1Handle); // Retoma a tarefa 1
            Serial.println("Tarefa 1 Retomada");
        } else if (command == '4') {
            vTaskResume(task2Handle); // Retoma a tarefa 2
            Serial.println("Tarefa 2 Retomada");
        }
    }
}