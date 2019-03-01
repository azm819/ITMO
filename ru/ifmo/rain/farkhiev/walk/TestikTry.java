package ru.ifmo.rain.farkhiev.walk;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.InvalidPathException;
import java.nio.file.Paths;
import java.util.Map;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class TestikTry {
    public static void main (String[] args) {
        Stream<String> s = Stream.of("apple", "banana", "apricot", "orange",
                "apple");
        Map<Character, String> m = s.collect(
                Collectors.toMap(s1 -> s1.charAt(0),
                        s1 -> s1,
                        (s1, s2) -> s1 + "|" + s2));
        System.out.println(m);
    }
}
