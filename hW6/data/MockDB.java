package data;

import java.util.ArrayList;

import models.course.Course;
import models.exceptions.CourseException;
import models.users.Student;
import services.StudentService;

/**
 * This class is used to store all the mock data of the application.
 * You could replace it by a real database or a file.
 */
public class MockDB {
    public ArrayList<Student> students = new ArrayList<Student>(){
        {
            // Add student users.
            add(new Student(0, "Alice"));
            add(new Student(1, "Bob"));
            add(new Student(2, "Cindy"));
            add(new Student(3, "Linda"));
            add(new Student(4, "Jessie"));
            add(new Student(5, "Tony"));
            add(new Student(6, "Peter"));
        }
    };

    public ArrayList<Course> courses = new ArrayList<Course>(){
        {
            try {
                // Add some classes.
                add(new Course("Data Structure", " F7-079", 40));
                add(new Course("Algorithms", " F7-059", 60));
                add(new Course("Operating Systems", "F7-119", 60));
                add(new Course("Digital IC Design", "P7-008", 2));
                add(new Course("Object-Oriented Software Engineering", "P7-042", 2));                
            } catch (IllegalAccessException e) {
                e.printStackTrace();
            }
        }
    };

    public MockDB() {
        Student Alice = (Student) students.get(0);
        Student Bob = (Student) students.get(1);
        Student Cindy = (Student) students.get(2);
        Student Linda = (Student) students.get(3);
        Student Jessie = (Student) students.get(4);
        Student Tony = (Student) students.get(5);
        Student Peter = (Student) students.get(6);

        Course dsCourse = (Course) courses.get(0);
        Course algoCourse = (Course) courses.get(1);        
        Course osCourse = (Course) courses.get(2);
        Course icCourse = (Course) courses.get(3);
        Course ooseCourse = (Course) courses.get(4);

        // Set algorithms as pre-requests of oose.
        algoCourse.setPreRequests(new ArrayList<>(){{
            add(dsCourse);
        }});
        ooseCourse.setPreRequests(new ArrayList<>(){{
            add(algoCourse);
            add(osCourse);
        }});

        // Set Alice passed algorithms.
        StudentService.passCourse(Alice, dsCourse);
        StudentService.passCourse(Bob, dsCourse);
        StudentService.passCourse(Bob, algoCourse);
        StudentService.passCourse(Cindy, dsCourse);
        StudentService.passCourse(Cindy, algoCourse);
        StudentService.passCourse(Cindy, osCourse);
        StudentService.passCourse(Linda, dsCourse);
        StudentService.passCourse(Linda, algoCourse);
        StudentService.passCourse(Linda, osCourse);
        StudentService.passCourse(Jessie, dsCourse);        
        StudentService.passCourse(Jessie, algoCourse);

        // Set Alice taken linear algebra.
        try {
            StudentService.takeCourse(Alice, icCourse);
            StudentService.takeCourse(Cindy, ooseCourse);
        } catch (CourseException e) {}
    }

    public Course getCourseByCode(String code) {
        for (Course course : courses) {
            if (course.getCode().equals(code)) {
                return course;
            }
        }
        return null;
    }

    public ArrayList<Student> getStudents() {
        return students;
    }

    public String getStudentList() {
        StringBuilder sb = new StringBuilder();
        int idx = 0;
        for (Student student : getStudents()) {
            sb.append(++idx + ' ').append(student.getName()).append(" ").append("\n");
        }
        return sb.toString();
    }

    public Student getStudentByName(String name) {
        for (Student student : getStudents()) {
            if (student.getName().equals(name)) {
                return student;
            }
        }
        return null;
    }
}
