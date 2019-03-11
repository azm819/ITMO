package ru.ifmo.rain.farkhiev.implementor;

import info.kgeorgiy.java.advanced.implementor.Impler;
import info.kgeorgiy.java.advanced.implementor.ImplerException;
import info.kgeorgiy.java.advanced.implementor.JarImpler;

import javax.tools.JavaCompiler;
import javax.tools.ToolProvider;
import java.io.BufferedWriter;
import java.io.File;
import java.io.IOException;
import java.lang.reflect.Method;
import java.lang.reflect.Modifier;
import java.net.URISyntaxException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.InvalidPathException;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Comparator;
import java.util.jar.Attributes;
import java.util.jar.JarOutputStream;
import java.util.jar.Manifest;
import java.util.zip.ZipEntry;


/**
 * Class that implements interfaces. Class implements interfaces and creates JAR-files. It depends on arguments
 *
 * @author Farkhiev
 * @version 1.0
 */
public class Implementor implements Impler, JarImpler {
    /** Constant for arguments of interface */
    private static final int ARGUMENTS_FOR_INTERFACE = 2;
    /** Constant for arguments of JAR*/
    private static final int ARGUMENTS_FOR_JAR = 3;

    /** String constant for SEPARATOR */
    private static final String SEPARATOR = File.separator;
    /** String constant for NEXT_LINE */
    private static final String NEXT_LINE = System.lineSeparator();
    /** String constant for "." */
    private static final String DOT = ".";
    /** String constant for "Impl" */
    private static final String IMPL = "Impl";
    /** String constant for ".java" */
    private static final String DOT_JAVA = ".java";
    /** String constant for ".class" */
    private static final String DOT_CLASS = ".class";
    /** String constant for "package " */
    private static final String PACKAGE = "package ";
    /** String constant for ""*/
    private static final String EMPTY_STRING = "";
    /** String constant for " " */
    private static final String SPACE = " ";
    /** String constant for ";" */
    private static final String SEMICOLON = ";";
    /** String constant for "{" */
    private static final String OPENING_FIGURED_BRACKET = "{";
    /** String constant for "}" */
    private static final String CLOSING_FIGURED_BRACKET = "}";
    /** String constant for "(" */
    private static final String OPENING_ROUND_BRACKET = "(";
    /** String constant for ")" */
    private static final String CLOSING_ROUND_BRACKET = ")";
    /** String constant for "public " */
    private static final String PUBLIC = "public ";
    /** String constant for "protected " */
    private static final String PROTECTED = "protected ";
    /** String constant for "class " */
    private static final String CLASS = "class ";
    /** String constant for " implements " */
    private static final String IMPLEMENTS = " implements ";
    /** String constant for " argument" */
    private static final String ARGUMENT = " argument";
    /** String constant for ", " */
    private static final String COMMA = ", ";
    /** String constant for " throws " */
    private static final String THROW = " throws ";
    /** String constant for "    return " */
    private static final String RETURN = "    return ";
    /** String constant for "false" */
    private static final String FALSE = "false";
    /** String constant for "null" */
    private static final String NULL = "null";
    /** String constant for "0" */
    private static final String ZERO = "0";

    /**
     * This function is used to choose which way of implementation to execute.
     * Runs {@link Implementor} in two possible ways:
     * <ul>
     * <li> 2 arguments: <code>className rootPath</code> - runs {@link #implement(Class, Path)} with first two arguments</li>
     * <li> 3 arguments: <code>-jar className jarPath</code> - runs {@link #implementJar(Class, Path)} with second two arguments</li>
     * </ul>
     * If arguments are incorrect or an error occurs during implementation returns message with information about error
     *
     * @param args an arguments
     */
    public static void main(String[] args) {
        boolean isJar;
        String name, fileName;
        switch (args.length) {
            case ARGUMENTS_FOR_INTERFACE:
                isJar = false;
                name = args[0];
                fileName = args[1];
                break;
            case ARGUMENTS_FOR_JAR:
                if (!args[0].equals("-jar")) {
                    System.err.println("Wrong arguments for JAR");
                    return;
                }
                isJar = true;
                name = args[1];
                fileName = args[2];
                break;
            default:
                System.err.println("Wrong number of arguments");
                return;

        }
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
            if (isJar) {
                implementor.implementJar(clazz, root);
            } else {
                implementor.implement(clazz, root);
            }
        } catch (ImplerException e) {
            System.err.println("Implementation error");
        }
    }

    /**
     * Generates an implementation. Generate full simple class implementation for this interface in following order:
     * <ol>
     * <li> Generates package: {@link #generatePackage(Class) generatePackage}</li>
     * <li> Generates declaration: {@link #generateDeclaration(Class) generateDeclaration}</li>
     * <li> Generates Methods: {@link #generateMethods(Class) generateMethods}</li>
     * </ol>
     *
     * @param token interface
     * @return Header, Body and Footer of class
     */
    private static StringBuilder generateImplementation(Class<?> token) {
        return new StringBuilder(generatePackage(token))
                .append(generateDeclaration(token))
                .append(OPENING_FIGURED_BRACKET)
                .append(generateMethods(token))
                .append(CLOSING_FIGURED_BRACKET)
                .append(NEXT_LINE);
    }

    /**
     * Generates package. Generates full package for class, if it exists, else returns <code>empty string</code>
     *
     * @param token interface
     * @return String. Package for class if exists
     */
    private static StringBuilder generatePackage(Class<?> token) {
        var result = new StringBuilder(EMPTY_STRING);
        if (!token.getPackageName().isEmpty()) {
            result.append(PACKAGE)
                    .append(token.getPackageName())
                    .append(SEMICOLON)
                    .append(NEXT_LINE);
        }
        return result;
    }

    /**
     * Generates declaration. Generates declaration of class before Body
     *
     * @param token class
     * @return StringBuilder declaration
     */
    private static StringBuilder generateDeclaration(Class<?> token) {
        String simpleName = token.getSimpleName();
        return new StringBuilder(PUBLIC)
                .append(CLASS)
                .append(simpleName)
                .append(IMPL)
                .append(IMPLEMENTS)
                .append(simpleName)
                .append(SPACE)
                .append(NEXT_LINE);
    }

    /**
     * Generates all methods.
     * Generates all public and private methods of interface in following order:
     * <ol>
     * <li> Chooses modifier: <code>PRIVATE</code> or <code>PUBLIC</code></li>
     * <li> Generates all of {@link Exception} if exists</li>
     * <li> Generate base <code>return</code> using {@link #getDefaultType(Class) getDefaultType}</li>
     * </ol>
     *
     * @param token class
     * @return Body, that contains methods
     */
    private static StringBuilder generateMethods(Class<?> token) {
        StringBuilder result = new StringBuilder(EMPTY_STRING);
        for (Method method : token.getMethods()) {
            var accessModifiers = method.getModifiers();
            String accessModifier = Modifier.isPublic(accessModifiers) ? PUBLIC : PROTECTED;
            result.append(accessModifier)
                    .append(method.getReturnType().getCanonicalName())
                    .append(SPACE)
                    .append(method.getName())
                    .append(OPENING_ROUND_BRACKET);
            Class[] parameterTypes = method.getParameterTypes();
            int length = parameterTypes.length;
            for (int i = 0; i < length - 1; ++i) {
                result.append(parameterTypes[i].getCanonicalName())
                        .append(ARGUMENT)
                        .append(i).append(COMMA);
            }
            if (length != 0) {
                result.append(parameterTypes[length - 1].getCanonicalName())
                        .append(ARGUMENT)
                        .append(length - 1);
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
        return result;
    }

    /**
     * Returns default type. Take a type and choose one of:
     * <ul>
     * <li> {@link #FALSE} for {@link Boolean}</li>
     * <li> {@link #EMPTY_STRING} for {@link String} and {@link Void}</li>
     * <li> {@link #ZERO} for {@link Integer}</li>
     * <li> {@link #NULL} for others</li>
     * </ul>
     *
     * @param type class
     * @return String of default parameter of any types
     */
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

    /**
     * Checks possibility of implementation class.
     *
     * @param token class
     * @throws ImplerException Error of implementation
     */
    private static void checkPossibility(Class<?> token) throws ImplerException {
        if (token.isPrimitive() || token.isArray() || token.isEnum() || Modifier.isFinal(token.getModifiers()) || token == Enum.class) {
            throw new ImplerException("Invalid class");
        }
    }

    /**
     * Generates implementation. Generates full implementation of this class for interface and print it in java-file
     *
     * @param token type token to create implementation for.
     * @param root  path
     * @throws ImplerException {@link ImplerException}. Error of implementation
     */
    @Override
    public void implement(Class<?> token, Path root) throws ImplerException {
        checkPossibility(token);
        root = root.resolve(token.getPackageName().replace(DOT, SEPARATOR));
        try {
            Files.createDirectories(root);
        } catch (IOException e) {
            System.out.println("Can't create directories");
        }

        try (BufferedWriter writer = Files.newBufferedWriter(Paths.get(root + SEPARATOR + token.getSimpleName() + IMPL + DOT_JAVA), StandardCharsets.UTF_8)) {
            writer.write(Implementor.generateImplementation(token).toString());
        } catch (SecurityException e) {
            System.err.println("Haven't access to output file");
        } catch (InvalidPathException e) {
            System.err.println("Wrong name of output Path");
        } catch (IOException e) {
            System.err.println("Cannot create writer");
        }
    }

    /**
     * Generates implementation and JAR-file for it. Generates full implementation of this class for interface and print it in java-file.
     * Then creates JAR-file and deletes temporary directory.
     * @see #deleteDirectory(Path) deleteDirectory
     *
     * @param token   type token to create implementation for.
     * @param jarFile <code>.jar</code> file.
     * @throws ImplerException {@link ImplerException}. Error of implementation
     */
    @Override
    public void implementJar(Class<?> token, Path jarFile) throws ImplerException {
        Path tempPath;
        try {
            tempPath = Files.createTempDirectory(jarFile.toAbsolutePath().getParent(), "newDirectory");
        } catch (IOException e) {
            throw new ImplerException("Can't create a temporary directory.", e);
        }
        try {
            implement(token, tempPath);
            compileFile(token, tempPath);
            createJar(token, jarFile, tempPath);
        } finally {
            deleteDirectory(tempPath);
        }
    }

    /**
     * Deletes temporary directory. Is used in {@link #implementJar(Class, Path) implementJar}
     *
     * @param tempPath Path, that is deleting
     */
    private void deleteDirectory(Path tempPath) {
        try {
            Files.walk(tempPath).sorted(Comparator.naturalOrder()).map(Path::toFile).forEach(File::delete);
        } catch (IOException e) {
            System.err.println("Can't delete the temporary directory.");
        }
    }

    /**
     * Creates jar. Is used in {@link #implementJar(Class, Path) implementJar}
     *
     * @param token    class
     * @param jarFile  Path to jar-file
     * @param tempPath Path to temporary directory
     * @throws ImplerException {@link ImplerException}. Error of implementation
     */
    private void createJar(Class<?> token, Path jarFile, Path tempPath) throws ImplerException {
        Manifest manifest = new Manifest();
        manifest.getMainAttributes().put(Attributes.Name.MANIFEST_VERSION, "1.0");
        try (var writer = new JarOutputStream(Files.newOutputStream(jarFile), manifest)) {
            writer.putNextEntry(new ZipEntry(token.getName().replace('.', '/') + IMPL + DOT + CLASS.trim()));
            Files.copy(getFilePath(tempPath, token, DOT_CLASS), writer);
        } catch (IOException e) {
            throw new ImplerException("Cannot write to JAR file", e);
        }
    }

    /**
     * Compiles file. Is used in {@link #implementJar(Class, Path) implementJar}
     *
     * @param token    class
     * @param tempPath Path to class
     * @throws ImplerException {@link ImplerException}. Error of implementation
     */
    private void compileFile(Class<?> token, Path tempPath) throws ImplerException {
        JavaCompiler compiler = ToolProvider.getSystemJavaCompiler();
        String[] args;
        args = new String[]{"-cp", tempPath.toString() + File.pathSeparator + getClassPath(token), getFilePath(tempPath, token, DOT_JAVA).toString()};
        if (compiler == null || compiler.run(null, null, null, args) != 0) {
            throw new ImplerException("Cannot compile file");
        }
    }

    /**
     * Returns string of path to class.
     *
     * @param token class
     * @return Path to class
     */
    private static String getClassPath(Class<?> token) {
        try {
            return Path.of(token.getProtectionDomain().getCodeSource().getLocation().toURI()).toString();
        } catch (final URISyntaxException e) {
            throw new AssertionError(e);
        }
    }

    /**
     * Returns path to compiled java-class.
     *
     * @param tempPath Path to temropapy directory
     * @param token    class
     * @param name     ".class" or ".java"
     * @return path to file
     */
    private Path getFilePath(Path tempPath, Class<?> token, String name) {
        return tempPath.resolve(token.getPackageName().replace('.', File.separatorChar)).resolve(token.getSimpleName() + IMPL + name);
    }
}
