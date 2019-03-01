package ru.ifmo.rain.farkhiev.walk;

import java.io.*;
import java.nio.charset.StandardCharsets;
import java.nio.file.*;

public class Walk {

    private static final int NUMBER_OF_ARGS = 2;
    private static final int FNV_32_PRIME = 0x01000193;
    private static final int BASE_HASH = 0x811c9dc5;
    private static final int ZERO_HASH = 0x00000000;
    private static final int BLOCK_SIZE = 1024;

    private static int getHashSum(final String fileName) {
        Path path;
        try {
            path = Paths.get(fileName);
        } catch (InvalidPathException e) {
            System.err.println("The request filName has deffects");
            return ZERO_HASH;
        }
        try (InputStream stream = Files.newInputStream(path)) {
            byte[] bytes = new byte[BLOCK_SIZE];
            int hash = BASE_HASH;
            int bytesRead;
            while ((bytesRead = stream.read(bytes)) >= 0) {
                for (int i = 0; i < bytesRead; i++) {
                    hash *= FNV_32_PRIME;
                    hash ^= bytes[i] & 0xff;
                }
            }
            return hash;
        } catch (NoSuchFileException e) {
            System.err.println("Request file is not found");
            return ZERO_HASH;
        } catch (SecurityException e) {
            System.err.println("Haven't an access to request file");
            return ZERO_HASH;
        } catch (IOException e) {
            System.err.println("Cannot read from request file");
            return ZERO_HASH;
        }
    }

    public static void main(String[] args) {
        if (args.length < NUMBER_OF_ARGS) {
            System.err.println("Too few parameters");
            return;
        }
        Path inputPath, outputPath;
        try {
            inputPath = Paths.get(args[0]);
            outputPath = Paths.get(args[1]);
        } catch (InvalidPathException e) {
            System.err.println("Cannot get path");
            return;
        }
        try {
            if (outputPath.getParent() != null) {
                Files.createDirectories(outputPath.getParent());
            }
        } catch (SecurityException e) {
            System.err.println("Haven't access to the directory");
            return;
        } catch (InvalidPathException e) {
            System.err.println("Wrong name of Path");
            return;
        } catch (IOException e) {
            System.err.println("Cannot create output directory");
            return;
        }
        try (BufferedReader reader = Files.newBufferedReader(inputPath, StandardCharsets.UTF_8)) {
            try (BufferedWriter writer = Files.newBufferedWriter(outputPath, StandardCharsets.UTF_8)) {
                String fileName;
                while ((fileName = reader.readLine()) != null) {
                    writer.write(String.join(" ", String.format("%08x", getHashSum(fileName)), fileName) + System.lineSeparator());
                }
            } catch (SecurityException e) {
                System.err.println("Haven't access to output file");
            } catch (InvalidPathException e) {
                System.err.println("Wrong name of output Path");
            } catch (IOException e) {
                System.err.println("Cannot create writer");
            }
        } catch (SecurityException e) {
            System.err.println("Haven't access to input file");
        } catch (InvalidPathException e) {
            System.err.println("Wrong name of input Path");
        } catch (IOException e) {
            System.err.println("Cannot create reader");
        }
    }
}
