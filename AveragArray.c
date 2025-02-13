int main() {
    int n;
    float sum = 0.0, average;

    
    printf("Enter the number of elements: ");
    scanf("%d", &n);

    
    float numbers[n];

    
    printf("Enter %d numbers:\n", n);
    for (int i = 0; i < n; i++) {
        printf("Number %d: ", i + 1);
        scanf("%f", &numbers[i]);
        sum += numbers[i]; // Add each number to sum
    }

  
    average = sum / n;

    
    printf("The average is: %.2f\n", average);

    return 0;
}
