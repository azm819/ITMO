package ru.ifmo.rain.farkhiev.walk;

import java.io.BufferedInputStream;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.InvalidPathException;
import java.nio.file.Path;
import java.nio.file.Paths;

public class RecursiveWalk {

    private static final int FNV_32_PRIME = 0x01000193;
    private static final int BASE_HASH = 0x811c9dc5;
    private static final int ZERO_HASH = 0x00000000;

    private static int getHashSum(final Path path) {
        int hash;
        try (BufferedInputStream stream = new BufferedInputStream(Files.newInputStream(path))) {
            hash = BASE_HASH;
            int bytesRead;
            while ((bytesRead = stream.read()) != -1) {
                hash *= FNV_32_PRIME;
                hash ^= bytesRead;
            }
        } catch (InvalidPathException e) {
            System.err.println("Cannot find request file");
            hash = ZERO_HASH;
        } catch (IOException e) {
            System.err.println("Cannot read from request file");
            hash = ZERO_HASH;
        }
        return hash;
    }

    private static void recursiveWalk(final Path path, final BufferedWriter writer) {
        if (Files.isDirectory(path)) {
            if (!Files.exists(path)) {
                try {
                    writer.write(String.format("%08x %s%n", ZERO_HASH, path));
                } catch (IOException e) {
                    System.err.println("Error with writing 2.0");
                }
                return;
            }
            try {
                Files.list(path).forEach(insideFiles -> recursiveWalk(insideFiles, writer));
            } catch (IOException e) {
                System.err.println("Error in Recursive walking");
            }
        } else {
            try {
                writer.write(String.format("%08x %s%n", getHashSum(path), path));
            } catch (IOException e) {
                System.err.println("Error with writing");
            }
        }
    }

    public static void main(String[] args) {
        try (BufferedReader reader = Files.newBufferedReader(Paths.get(args[0]), StandardCharsets.UTF_8);
             BufferedWriter writer = Files.newBufferedWriter(Paths.get(args[1]), StandardCharsets.UTF_8)) {
            String fileName;
            while ((fileName = reader.readLine()) != null) {
                try {
                    recursiveWalk(Paths.get(fileName), writer);
                } catch (InvalidPathException e) {
                    writer.write(String.join(" ", String.format("%08x", ZERO_HASH), fileName) + System.lineSeparator());
                }
            }
        } catch (IndexOutOfBoundsException e) {
            System.err.println("Too few parameters");
        } catch (InvalidPathException e) {
            System.err.println("Cannot find one of these files");
        } catch (IOException e) {
            System.err.println("Cannot read or write");
        }
    }
}
