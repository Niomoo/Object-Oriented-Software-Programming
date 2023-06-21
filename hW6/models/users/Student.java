package models.users;

import java.util.ArrayList;

import models.course.Course;
import models.roles.StudentRole;

/**
 * The Student class.
 */
public class Student implements StudentRole {

    // The id of the student.
    private int id;

    // The name of the student.
    private String name;

    // The role of the student.
    private int permission;

    // The courses that the student has registered.
    private ArrayList<Course> register = new ArrayList<>();

    // The courses that the student has passed.
    private ArrayList<Course> passed = new ArrayList<>();

    /**
     * The constructor of Student.
     * 
     * @param id The id of the student.
     * @param name The name of the student.
     */
    public Student(int id, String name, int permission) {
        setId(id);
        setName(name);
        setPermission(permission);
    }

    @Override
    public void setId(int paramInt) {
        this.id = paramInt;
    }

    @Override
    public int getId() {
        return id;
    }

    @Override
    public void setName(String paramString) {
        name = paramString;
    }

    @Override
    public String getName() {
        return name;
    }

    @Override
    public void setPermission(int paramInt) {
        permission = paramInt;
    }

    @Override
    public int getPermission() {
        return permission;
    }

    @Override
    public String toString() {
        return "Student{" +
                "name=" + getName() +
                ", registered=" + Course.getCourseString(register) +
                ", passed=" + Course.getCourseString(passed) +
                '}';
    }

    /**
     * Return a formatted string of the student information.
     * 
     * @return A formatted string.
     */
    public String getInfoString() {
        return "name: " + getName() +
               "\ntaken courses: " + Course.getCourseString(register) +
               "\npassed courses: " + Course.getCourseString(passed);
    }

    /**
     * Return a formatted string of the students' information.
     * 
     * @param students The students.
     * @return The formatted string.
     */
    public static String getStudentLiString(ArrayList<Student> students) {
        StringBuilder sb = new StringBuilder();

        sb.append(String.format("%6s %s\n", "Select", "Name"));

        for (int i=0; i<students.size(); i++) {
            Student student = students.get(i);
            sb.append(String.format("  [%2d] %s\n", i, student.getName()));
        }

        return sb.toString();
    }

    public ArrayList<Course> getPassed() {
        return passed;
    }

    public void setPassed(ArrayList<Course> passed) {
        this.passed = passed;
    }

    public ArrayList<Course> getRegister() {
        return register;
    }

    public void setRegister(ArrayList<Course> register) {
        this.register = register;
    }
}
