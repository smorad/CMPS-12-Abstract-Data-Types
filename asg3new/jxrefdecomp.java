import java.io.*;
import java.util.Scanner;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

class jxref
{
    /* member class not found */
    class print_visitor {}

    /* member class not found */
    class string_cqueue_map {}


    jxref()
    {
    }

    static void scanfile(String filename, Scanner file, options opts)
    {
        System.out.printf("filename = %s%n", new Object[] {
            filename
        });
        string_cqueue_map tree = new string_cqueue_map();
        for(int linenr = 1; file.hasNextLine(); linenr++)
        {
            String line = file.nextLine();
            for(Matcher matcher = WORD_PATTERN.matcher(line); matcher.find();)
            {
                String word = matcher.group();
                counted_queue queue = (counted_queue)tree.get(word);
                if(queue != null)
                {
                    queue.insert(Integer.valueOf(linenr));
                } else
                {
                    queue = new counted_queue();
                    queue.insert(Integer.valueOf(linenr));
                    tree.put(word, queue);
                }
            }

        }

        if(opts.dump_tree)
            tree.debug_dump();
        else
            tree.visit_all(new print_visitor(opts.count_only));
    }

    public static void main(String args[])
    {
        options opts = new options(args);
        String arr$[] = opts.filenames;
        int len$ = arr$.length;
        for(int i$ = 0; i$ < len$; i$++)
        {
            String filename = arr$[i$];
            if(filename == null)
                continue;
            if(filename.equals("-"))
            {
                scanfile("-", new Scanner(System.in), opts);
                continue;
            }
            try
            {
                Scanner scan = new Scanner(new File(filename));
                scanfile(filename, scan, opts);
                scan.close();
            }
            catch(IOException error)
            {
                messages.warn(new Object[] {
                    error.getMessage()
                });
            }
        }

        System.exit(messages.exit_status);
    }

    static final String WORD_REGEX = "\\w+([-'.:/]\\w+)*";
    static final Pattern WORD_PATTERN = Pattern.compile("\\w+([-'.:/]\\w+)*");

}

