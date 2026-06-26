import java.util.Scanner;

public class reversing {

    public static int reverse(int x) {
        int rev = 0;

        while (x != 0) {
            int digit = x % 10;

            // Check for positive overflow
            if (rev > Integer.MAX_VALUE / 10 ||
                (rev == Integer.MAX_VALUE / 10 && digit > 7)) {
                return 0;
            }

            // Check for negative overflow
            if (rev < Integer.MIN_VALUE / 10 ||
                (rev == Integer.MIN_VALUE / 10 && digit < -8)) {
                return 0;
            }

            rev = rev * 10 + digit;
            x = x / 10;
        }

        return rev;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.print("Enter an integer: ");
        int x = sc.nextInt();

        int result = reverse(x);

        System.out.println("Reversed Integer: " + result);

        sc.close();
    }
}