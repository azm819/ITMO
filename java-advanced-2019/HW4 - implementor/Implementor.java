package ru.ifmo.rain.farkhiev.implementor;

import info.kgeorgiy.java.advanced.implementor.Impler;
import info.kgeorgiy.java.advanced.implementor.ImplerException;

import java.io.BufferedWriter;
import java.io.File;
import java.io.IOException;
import java.lang.reflect.Method;
import java.lang.reflect.Modifier;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.InvalidPathException;
import java.nio.file.Path;
import java.nio.file.Paths;

public class Implementor implements Impler {

    private static final int NUMBER_OF_ARGUMENTS = 2;

    private static final String SEPARATOR = File.separator;
    private static final String NEXT_LINE = System.lineSeparator();
    private static final String DOT = ".";
    private static final String IMPL = "Impl";
    private static final String JAVA = "java";
    private static final String PACKAGE = "package ";
    private static final String EMPTY_STRING = "";
    private static final String SPACE = " ";
    private static final String SEMICOLON = ";";
    private static final String OPENING_FIGURED_BRACKET = "{";
    private static final String CLOSING_FIGURED_BRACKET = "}";
    private static final String OPENING_ROUND_BRACKET = "(";
    private static final String CLOSING_ROUND_BRACKET = ")";
    private static final String PUBLIC = "public ";
    private static final String CLASS = "class ";
    private static final String IMPLEMENTS = " implements ";
    private static final String ARGUMENT = " argument";
    private static final String COMMA = ", ";
    private static final String THROW = " throws ";
    private static final String RETURN = "    return ";
    private static final String FALSE = "false";
    private static final String NULL = "null";
    private static final String ZERO = "0";

    public static void main(String[] args) {
        if (args.length < NUMBER_OF_ARGUMENTS) {
            System.err.println("Too few arguments");
            return;
        }
        String name = args[0], fileName = args[1];
        Path root;
        try {
            root = Paths.get(fileName);
        } catch (InvalidPathException e) {
            System.err.println("Cannot get path");
            return;
        }
        Class clazz;
        try {
            clazz = Class.forName(name);
        } catch (ClassNotFoundException e) {
            System.err.println("Cannot get class");
            return;
        }
        try {
            Implementor implementor = new Implementor();
            implementor.implement(clazz, root);
        } catch (ImplerException e) {
            System.err.println("Implementation error");
        }
    }

    @Override
    public void implement(Class<?> token, Path root) throws ImplerException {
        if (token.isPrimitive() || token.isArray() || token.isEnum() || Modifier.isFinal(token.getModifiers()) || token == Enum.class) {
            throw new ImplerException("Invalid class");
        }

        root = root.resolve(token.getPackageName().replace(DOT, SEPARATOR));
        try {
            Files.createDirectories(root);
        } catch (IOException e) {
            System.out.println("Can't create directories");
        }

        try (BufferedWriter writer = Files.newBufferedWriter(Paths.get(root + SEPARATOR + token.getSimpleName() + IMPL + DOT + JAVA), StandardCharsets.UTF_8)) {
            writer.write(Implementor.generateImplementation(token));
        } catch (SecurityException e) {
            System.err.println("Haven't access to output file");
        } catch (InvalidPathException e) {
            System.err.println("Wrong name of output Path");
        } catch (IOException e) {
            System.err.println("Cannot create writer");
        }
    }

    private static String generateImplementation(Class<?> token) {
        return generatePackage(token) + generateDeclaration(token) + OPENING_FIGURED_BRACKET + generateMethods(token) + CLOSING_FIGURED_BRACKET + NEXT_LINE;
    }

    private static String generatePackage(Class<?> token) {
        return PACKAGE + token.getPackageName() + SEMICOLON + NEXT_LINE;
    }

    private static String generateDeclaration(Class<?> token) {
        String simpleName = token.getSimpleName();
        return PUBLIC + CLASS + simpleName + IMPL + IMPLEMENTS + simpleName + SPACE + NEXT_LINE;
    }

    private static String generateMethods(Class<?> token) {
        StringBuilder result = new StringBuilder(EMPTY_STRING);
        for (Method method : token.getMethods()) {
            result.append(PUBLIC)
                    .append(method.getReturnType().getCanonicalName())
                    .append(SPACE)
                    .append(method.getName())
                    .append(OPENING_ROUND_BRACKET);
            Class[] parameterTypes = method.getParameterTypes();
            int length = parameterTypes.length;
            for (int i = 0; i < length - 1; ++i) {
                result.append(parameterTypes[i].getCanonicalName())
                        .append(ARGUMENT).append(i).append(COMMA);
            }
            if(length != 0){
                result.append(parameterTypes[length - 1].getCanonicalName()).append(ARGUMENT).append(length - 1);
            }
            result.append(CLOSING_ROUND_BRACKET);
            Class[] exceptions = method.getExceptionTypes();
            length = exceptions.length;
            if (length != 0) {
                result.append(THROW);
                for (int i = 0; i < length - 1; ++i) {
                    result.append(exceptions[i].getName())
                            .append(COMMA);
                }
                result.append(exceptions[length - 1].getName());
            }
            result.append(OPENING_FIGURED_BRACKET)
                    .append(NEXT_LINE)
                    .append(RETURN)
                    .append(getDefaultType(method.getReturnType()))
                    .append(SEMICOLON)
                    .append(NEXT_LINE)
                    .append(CLOSING_FIGURED_BRACKET)
                    .append(NEXT_LINE);
        }
        return result.toString();
    }

    private static String getDefaultType(Class type) {
        if (type.isPrimitive()) {
            if (Boolean.TYPE.equals(type))
                return FALSE;
            else if (Void.TYPE.equals(type))
                return EMPTY_STRING;
            else
                return ZERO;
        } else
            return NULL;
    }
}
