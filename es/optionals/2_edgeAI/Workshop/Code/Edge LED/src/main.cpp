#include <PDM.h>
#include <Voice_try_inferencing.h>  // Your Edge Impulse library

// Built-in RGB pins (active-low)
#define LEDR 22  // Red
#define LEDG 23  // Green
#define LEDB 24  // Blue

// Audio buffers
typedef struct {
    int16_t *buffer;
    uint8_t buf_ready;
    uint32_t buf_count;
    uint32_t n_samples;
} inference_t;

static inference_t inference;
static int16_t sampleBuffer[2048];
static bool debug_nn = false;

// ------------------- Microphone functions -------------------
static void pdm_data_ready_inference_callback(void) {
    int bytesAvailable = PDM.available();
    int bytesRead = PDM.read((char *)&sampleBuffer[0], bytesAvailable);

    if (inference.buf_ready == 0) {
        for (int i = 0; i < (bytesRead >> 1); i++) {
            inference.buffer[inference.buf_count++] = sampleBuffer[i];
            if (inference.buf_count >= inference.n_samples) {
                inference.buf_count = 0;
                inference.buf_ready = 1;
                break;
            }
        }
    }
}

static bool microphone_inference_start(uint32_t n_samples) {
    inference.buffer = (int16_t *)malloc(n_samples * sizeof(int16_t));
    if (!inference.buffer) return false;

    inference.buf_count = 0;
    inference.n_samples = n_samples;
    inference.buf_ready = 0;

    PDM.onReceive(&pdm_data_ready_inference_callback);
    PDM.setBufferSize(4096);

    if (!PDM.begin(1, EI_CLASSIFIER_FREQUENCY)) { // mono, 16kHz
        ei_printf("Failed to start PDM!\n");
        free(inference.buffer);
        return false;
    }

    PDM.setGain(127);
    return true;
}

static bool microphone_inference_record(void) {
    inference.buf_ready = 0;
    inference.buf_count = 0;
    while (inference.buf_ready == 0) delay(10);
    return true;
}

static int microphone_audio_signal_get_data(size_t offset, size_t length, float *out_ptr) {
    numpy::int16_to_float(&inference.buffer[offset], out_ptr, length);
    return 0;
}

static void microphone_inference_end(void) {
    PDM.end();
    free(inference.buffer);
}

// ------------------- RGB color cycle -------------------
void runColorCycle() {
    int delayTime = 500; // milliseconds

    // WHITE
    digitalWrite(LEDR, LOW); digitalWrite(LEDG, LOW); digitalWrite(LEDB, LOW); delay(delayTime);
    // RED
    digitalWrite(LEDR, LOW); digitalWrite(LEDG, HIGH); digitalWrite(LEDB, HIGH); delay(delayTime);
    // GREEN
    digitalWrite(LEDR, HIGH); digitalWrite(LEDG, LOW); digitalWrite(LEDB, HIGH); delay(delayTime);
    // BLUE
    digitalWrite(LEDR, HIGH); digitalWrite(LEDG, HIGH); digitalWrite(LEDB, LOW); delay(delayTime);
    // YELLOW
    digitalWrite(LEDR, LOW); digitalWrite(LEDG, LOW); digitalWrite(LEDB, HIGH); delay(delayTime);
    // MAGENTA
    digitalWrite(LEDR, LOW); digitalWrite(LEDG, HIGH); digitalWrite(LEDB, LOW); delay(delayTime);
    // CYAN
    digitalWrite(LEDR, HIGH); digitalWrite(LEDG, LOW); digitalWrite(LEDB, LOW); delay(delayTime);
    // OFF
    digitalWrite(LEDR, HIGH); digitalWrite(LEDG, HIGH); digitalWrite(LEDB, HIGH); delay(delayTime);
}

// ------------------- Setup -------------------
void setup() {
    Serial.begin(115200);
    while (!Serial);

    pinMode(LEDR, OUTPUT);
    pinMode(LEDG, OUTPUT);
    pinMode(LEDB, OUTPUT);

    Serial.println("Edge Impulse + RGB LED Color Cycle Demo");

    if (!microphone_inference_start(EI_CLASSIFIER_RAW_SAMPLE_COUNT)) {
        ei_printf("ERR: Could not allocate audio buffer\n");
        while (1); // stop
    }
}

// ------------------- Loop -------------------
void loop() {
    ei_printf("Starting inferencing in 2 seconds...\n");
    delay(2000);

    ei_printf("Recording...\n");
    microphone_inference_record();
    ei_printf("Recording done\n");

    signal_t signal;
    signal.total_length = EI_CLASSIFIER_RAW_SAMPLE_COUNT;
    signal.get_data = &microphone_audio_signal_get_data;
    ei_impulse_result_t result = {0};

    EI_IMPULSE_ERROR r = run_classifier(&signal, &result, debug_nn);
    if (r != EI_IMPULSE_OK) {
        ei_printf("ERR: Failed to run classifier (%d)\n", r);
        return;
    }

    // Print results
    ei_printf("Predictions (DSP: %d ms, Classification: %d ms, Anomaly: %d ms):\n",
              result.timing.dsp, result.timing.classification, result.timing.anomaly);

    for (size_t ix = 0; ix < EI_CLASSIFIER_LABEL_COUNT; ix++) {
        ei_printf("    %s: %.5f\n", result.classification[ix].label, result.classification[ix].value);
    }

#if EI_CLASSIFIER_HAS_ANOMALY == 1
    ei_printf("    anomaly score: %.3f\n", result.anomaly);
#endif

    // If "Hey Edge" is detected with confidence > 0.8, run color cycle
    if (result.classification[0].value > 0.8) {
        runColorCycle();
    }
}
